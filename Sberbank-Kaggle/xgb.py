# import
import pandas as pd
import xgboost as xgb
import sklearn as skl

# load data
train = pd.read_csv('../input/train.csv')
test = pd.read_csv('../input/test.csv')

# encode data
def encode(df):
    df = df.drop(['id', 'timestamp'], 1)
    for c in df.columns:
        if df[c].dtype == 'object':
            df[c] = skl.preprocessing.LabelEncoder().fit_transform(list(df[c].values))
    return df
dtrain = xgb.DMatrix(encode(train.drop(['price_doc'], 1)), train['price_doc'])
dtest = xgb.DMatrix(encode(test))

# train and get result
param = {'eta': .05, 'max_depth': 5, 'objective': 'reg:linear', 'eval_metric': 'rmse'}
result = pd.DataFrame({'id': test.id, 'price_doc': xgb.train(param, dtrain, 500).predict(dtest)})
result.to_csv('xgb.csv', index=0)

