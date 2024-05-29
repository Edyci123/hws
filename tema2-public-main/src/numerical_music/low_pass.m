function filtered_signal = low_pass(signal, fs, cutoff_freq)
    N = length(signal);

    fft_signal = fft(signal);
    
    freq = (0:N-1) * fs / N;

    mask = freq <= cutoff_freq;

    fft_filtered_signal = fft_signal .* mask';

    filtered_signal = ifft(fft_filtered_signal);

    filtered_signal = filtered_signal / max(abs(filtered_signal))
end