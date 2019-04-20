import numpy as np
import pandas as pd

a = pd.read_csv('input/a380.csv')
b = pd.read_csv('input/a391.csv')

res = a.merge(b, on='id', suffixes=['a', 'b'])
res['price_doc'] = np.exp(np.log(res.price_doca) * (1 - np.exp(-1)) + np.log(res.price_docb) * np.exp(-1))
res.drop(['price_doca', 'price_docb'], axis=1, inplace=True)
res.to_csv('sub.csv', index=False)

