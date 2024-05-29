from flask import Blueprint, request, current_app, redirect, url_for, flash, render_template, send_from_directory
from flask import session
from PIL import Image
from werkzeug.utils import secure_filename
import os

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in current_app.config['ALLOWED_EXTENSIONS']
           
def get_images_by_category():
    categories = {}
    base_folder = current_app.config['UPLOAD_FOLDER']
    
    for category in os.listdir(base_folder):
        cat_path = os.path.join(base_folder, category)
        if os.path.isdir(cat_path):
            categories[category] = []
            for img in os.listdir(cat_path):
                if allowed_file(img) and 'thumb' in img:
                    img_path = os.path.join(category, img)
                    categories[category].append(img_path)
    return categories


def save_thumbnail(image_path, base_path, thumb_name):
    size = (200, 200)  # Size of the thumbnail
    with Image.open(image_path) as img:
        img.thumbnail(size)
        thumb_path = os.path.join(base_path, thumb_name)
        img.save(thumb_path)


main = Blueprint('main', __name__)

@main.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('main.login'))
    return render_template('index.html', name=session['username'])

@main.route('/about')
def about():
    if not session.get('logged_in'):
        return redirect(url_for('main.login'))
    return render_template('about.html')

@main.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == "admin" and password == "password":
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('main.index'))
        else:
            return render_template('login.html', msg="Invalid credentials!")

    return render_template('login.html', msg="")

@main.route('/gallery')
def gallery():
    if not session.get('logged_in'):
        return redirect(url_for('main.login'))
    images = get_images_by_category()
    return render_template('gallery.html', images=images)

@main.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('username', None)
    return redirect(url_for('main.login'))

@main.route('/load', methods=["GET"])
def load():
    return send_from_directory(directory='uploads', path="Bbmm.jpeg")


@main.route('/upload', methods=['POST'])
def upload_file():
    print("Received form data:", request.form)
    if 'image' not in request.files:
        flash('No file part')
        return redirect(request.url)
    file = request.files['image']
    name = request.form['name']
    category = request.form['category']
    if file.filename == '':
        flash('No selected file')
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file_extension = filename.rsplit('.', 1)[1]
        save_path = os.path.join(current_app.config['UPLOAD_FOLDER'], category)
        if not os.path.exists(save_path):
            os.makedirs(save_path)
        full_filename = f"{name}.{file_extension}"
        full_path = os.path.join(save_path, full_filename)
        file.save(full_path)

        thumb_filename = f"{name}.thumb.{file_extension}"
        save_thumbnail(full_path, save_path, thumb_filename)

        flash('File and thumbnail uploaded successfully')
        return redirect(url_for('main.gallery'))
    else:
        flash('File type not allowed')
        return redirect(request.url)