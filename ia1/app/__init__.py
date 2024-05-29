from flask import Flask

def create_app():
    app = Flask(__name__, static_folder='uploads')
    app.secret_key = 'AmAcasaUnTezaurCloscaCuPuiiDeAur'
    app.config['UPLOAD_FOLDER'] = 'app/uploads/'  # Folder where uploaded files will be stored
    app.config['ALLOWED_EXTENSIONS'] = {'png', 'jpg', 'jpeg', 'gif'}  # Allowed image types


    from .routes import main
    app.register_blueprint(main)

    return app