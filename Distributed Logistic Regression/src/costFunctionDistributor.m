function [J, grad] = costFunctionDistributor(k, m, theta, X, y)

J = 0;
grad = zeros(size(theta));

% parallel computing of the cost function and gradient
parfor i = 1:k
    [Jtemp, Gtemp] = costFunctionBatch(m, theta, X(:, :, i), y(:, i));
    J = J + Jtemp;
    grad = grad + Gtemp;
end

end
