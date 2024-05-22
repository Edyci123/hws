function filtered_signal = low_pass(signal, fs, cutoff_freq)
    % Length of the signal
    N = length(signal);

    % FFT of the original signal
    fft_signal = fft(signal);

    % Create a frequency vector
    if mod(N, 2) == 0
        f = (-N/2:N/2-1)*(fs/N);
    else
        f = (-(N-1)/2:(N-1)/2)*(fs/N);
    end
    f = fftshift(f); % Shift zero frequency to center

    % Generate the mask based on the cutoff frequency
    mask = abs(f) <= cutoff_freq;

    % Apply the mask in frequency domain
    fft_signal_shifted = fftshift(fft_signal); % Shift zero frequency to center
    fft_filtered_signal = fft_signal_shifted .* mask;

    % Shift back and perform inverse FFT
    fft_filtered_signal = ifftshift(fft_filtered_signal);
    filtered_signal = ifft(fft_filtered_signal, 'symmetric');

    % No normalization step included, handle outside if necessary
end