function similarity = cosine_similarity(A, B)
    similarity = dot(A / norm(A), B / norm(B));
end
