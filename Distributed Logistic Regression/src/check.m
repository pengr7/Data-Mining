% initialize
clear; clc;

% load data
train = csvread('train.csv');
test = csvread('test.csv');

% simplify data
Xtrain = [ones(60000, 1) train(:, 100:10:600)];
ytrain = train(:, 785) >= 5;
Xtest = [ones(10000, 1) test(:, 100:10:600)];
ytest = test(:, 785) >= 5;
init_theta = zeros(size(Xtrain, 2), 1);
param = optimset('GradObj', 'on', 'MaxIter', 100);

% Batch gradient descent
tic;
[theta1, cost1] = fminunc(@(t)(costFunctionBatch...
    (60000, t, Xtrain, ytrain)), init_theta, param);
pred1 = sigmoid(Xtest * theta1) >= .5;
acc1 = sum(pred1 == ytest) / 10000;
t1 = toc;

% Distributed gradient descent
tic;
Dx = zeros(15000, size(Xtrain, 2), 4);
Dy = zeros(15000, 4);
for i = 1:4
    Dx(:, :, i) = Xtrain(15000 * i - 14999:15000 * i, :);
    Dy(:, i) = ytrain(15000 * i - 14999:15000 * i);
end
[theta2, cost2] = fminunc(@(t)(costFunctionDistributor...
    (4, 60000, t, Dx, Dy)), init_theta, param);
pred2 = sigmoid(Xtest * theta2) >= .5;
acc2 = sum(pred2 == ytest) / 10000;
t2 = toc;
