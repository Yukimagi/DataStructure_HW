# plot.py
import sys
import matplotlib.pyplot as plt
def PLOT(filename,title):
  sys.stdin = open(filename,'r',encoding='utf-8')
  data = [float(i) for i in input().split()] # Split the data into x and y values
  x = [i for i in range(len(data))]
  y = data
  plt.plot(x, y)
  plt.title = title
  plt.xlabel('Term')
  plt.ylabel('Price')
  plt.show()
PLOT('test1.txt','Close_price')
PLOT('test2.txt','dayily return')
PLOT('test3.txt','intraday return')