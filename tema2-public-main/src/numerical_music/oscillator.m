function x = oscillator(freq, fs, dur, A, D, S, R)
    t = 0:1/fs:dur-1/fs;

    y = sin(2*pi*freq*t)';

    numSamples = length(t);
    attackSamples = floor(A * fs);
    decaySamples = floor(D * fs);
    releaseSamples = floor(R * fs);
    sustainSamples = numSamples - (attackSamples + decaySamples + releaseSamples);

    attackEnv = linspace(0, 1, attackSamples)';

    decayEnv = linspace(1, S, decaySamples)';

    sustainEnv = S * ones(sustainSamples, 1);

    releaseEnv = linspace(S, 0, releaseSamples)';

    envelope = [attackEnv; decayEnv; sustainEnv; releaseEnv];

    x = y .* envelope;
end