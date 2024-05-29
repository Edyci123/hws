function signal = apply_reverb(signal, impulse_response)
    % Ensure impulse response is mono
    impulse_response = stereo_to_mono(impulse_response);

    % Compute the convolution of the signal with the impulse response
    % using fft-based convolution for efficiency
    convolved_signal = conv(signal, impulse_response, 'full');

    % Normalize the resulting signal to prevent clipping
    % The normalization factor is the maximum absolute value of the convolved signal
    max_val = max(abs(convolved_signal));
    if max_val > 0  % Avoid division by zero
        signal = convolved_signal / max_val;
    else
        signal = convolved_signal;  % In case the max_val is zero
    end
end