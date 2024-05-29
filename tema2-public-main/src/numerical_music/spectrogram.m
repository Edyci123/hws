function [S, f, t] = spectrogram(signal, fs, window_size)
    num_windows = floor(length(signal) / window_size);
    
    S = zeros(floor(window_size), num_windows);
    
    hann_window = hanning(window_size);
    
    for k = 1:num_windows
        window_start = (k-1)*window_size + 1;
        window_end = k*window_size;
        windowed_signal = signal(window_start:window_end) .* hann_window;
        
        fft_result = fft(windowed_signal, 2*window_size);
        
        S(:, k) = abs(fft_result(1:window_size));
    end
    
    f = (0:floor(window_size-1))' * (fs / (2*window_size));
    
    t = ((0:num_windows-1) * window_size / fs)';
end