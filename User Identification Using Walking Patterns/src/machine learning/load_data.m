% init
data = [];
num_users = 18;

% read data
for i=1:num_users
    temp = readmatrix(strjoin({'data_copy/', num2str(i), '.csv'}, ''));
    data = [data; temp];
end

% split into training and test sets
data_size = length(data);
split_point = round(0.8 * data_size);
data = data(randperm(data_size), :);
train = data(1:split_point, :);
test = data(1+split_point:end, :);

% write data
writematrix(train, 'train.csv');
writematrix(test, 'test.csv');
