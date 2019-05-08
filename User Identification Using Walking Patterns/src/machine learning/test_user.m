function res = test_user(mdl, test)
res = zeros(22, 4);
for id=1:22
    res(id, :) = [id accu_sens_spec(mdl, test, id)];
end

function res = accu_sens_spec(mdl, test, id)
actual = test(:, end);
predict = mdl.predictFcn(test(:, 1:end-1));
TP = 0;
TN = 0;
FP = 0;
FN = 0;
for i=1:size(test, 1)
    if actual(i) == id && predict(i) == id
        TP = TP + 1;
    end
    if actual(i) ~= id && predict(i) == id
        FP = FP + 1;
    end
    if actual(i) == id && predict(i) ~= id
        FN = FN + 1;
    end
    if actual(i) ~= id && predict(i) ~= id
        TN = TN + 1;
    end
end
res = [(TP+TN)/(TP+FP+FN+TN) TP/(TP+FN) TN/(TN+FP)];


