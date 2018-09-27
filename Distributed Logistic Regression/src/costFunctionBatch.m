function [J, grad] = costFunctionBatch(m, theta, X, y)

activated = sigmoid(X * theta);
J = - (1 / m) * sum(y .* log(activated) + (1 - y) .* log(1 - activated));
grad = (1 / m) * X' * (activated - y);

end
