function [error_train, error_val] = ...
    learningCurveModified(X, y, Xval, yval, lambda)
m = size(X, 1);
error_train = zeros(m, 1);
error_val   = zeros(m, 1);
for i = 1:m
    chosen1 = randsample(m, i);
    theta = trainLinearReg(X(chosen1, :), y(chosen1), lambda);
    error_train(i) = linearRegCostFunction(X(chosen1, :), y(chosen1), theta, 0);
    
    chosen2 = randsample(size(Xval, 1), i);
    error_val(i) = linearRegCostFunction(Xval(chosen2, :), yval(chosen2), theta, 0);
end

end
