function recoms = recommendations(path, liked_theme, num_recoms, min_reviews, num_features)
    preprocessed_mat = preprocess(read_mat(path), min_reviews);
 
    [U, S, V] = svds(preprocessed_mat, num_features);
 
    liked = V(liked_theme,:);
 
    for i = 1:size(V, 1)
        similarities(i) = cosine_similarity(liked, V(i, :)');
    endfor
 
    [sorted, sorted_idx] = sort(similarities, 'descend');
 
    recoms = sorted_idx(2:(1+num_recoms));
end