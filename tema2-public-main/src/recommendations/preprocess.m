function reduced_mat = preprocess(mat, min_reviews)
    rows_to_keep = [];
    
    for i = 1:size(mat, 1)
        if nnz(mat(i, :)) >= min_reviews
            rows_to_keep = [rows_to_keep; i];
        endif
    endfor
    
    reduced_mat = mat(rows_to_keep, :);
end
