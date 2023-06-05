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
PLOT('test4.txt','Close_price')
PLOT('test5.txt','dayily return')
PLOT('test6.txt','intraday return')