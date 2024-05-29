function [S, f, t] = spectrogram(signal, fs, window_size)
    % Function to compute the spectrogram of a given signal
    %
    % Inputs:
    %   signal - the input signal
    %   fs - sampling rate of the signal
    %   window_size - size of each window to apply FFT
    
    % Number of windows
    num_windows = floor(length(signal) / window_size);
    
    % Pre-allocate the spectrogram matrix, only half the FFT size due to symmetry
    S = zeros(floor(window_size/2)+1, num_windows);
    
    % Hann window function
    hann_window = hanning(window_size);
    
    % Compute the spectrogram
    for k = 1:num_windows
        % Extract the window of the signal
        window_start = (k-1)*window_size + 1;
        window_end = k*window_size;
        windowed_signal = signal(window_start:window_end) .* hann_window;
        
        % Fourier Transform of the window
        fft_result = fft(windowed_signal, 2*window_size);  % Compute FFT with zero-padding
        
        % Take the magnitude of the first half of the FFT result (positive frequencies)
        S(:, k) = abs(fft_result(1:floor(window_size/2)+1));
    end
    
    % Frequency vector (only positive frequencies)
    f = (0:floor(window_size/2))' * (fs / (2*window_size));
    
    % Time vector
    t = ((0:num_windows-1) * window_size / fs)';
end