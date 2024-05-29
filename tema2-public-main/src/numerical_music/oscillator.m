function x = oscillator(freq, fs, dur, A, D, S, R)
    % Create a time vector 't' from 0 to 'dur' with a step of 1/'fs'
    t = 0:1/fs:dur-1/fs;

    % Create the sine wave
    y = sin(2*pi*freq*t)';

    % Calculate the number of samples for each phase of the envelope
    numSamples = length(t);
    attackSamples = floor(A * fs);
    decaySamples = floor(D * fs);
    releaseSamples = floor(R * fs);
    sustainSamples = numSamples - (attackSamples + decaySamples + releaseSamples);

    % Generate the attack envelope (linear ramp from 0 to 1)
    attackEnv = linspace(0, 1, attackSamples)';

    % Generate the decay envelope (linear ramp from 1 to S)
    decayEnv = linspace(1, S, decaySamples)';

    % Generate the sustain envelope (constant value S)
    sustainEnv = S * ones(sustainSamples, 1);

    % Generate the release envelope (linear ramp from S to 0)
    releaseEnv = linspace(S, 0, releaseSamples)';

    % Concatenate all parts of the envelope
    envelope = [attackEnv; decayEnv; sustainEnv; releaseEnv];

    % Apply the envelope to the sine wave (Hadamard product)
    x = y .* envelope;
end