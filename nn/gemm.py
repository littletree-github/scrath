import theano
from theano import tensor as T
from theano import shared, function
from numpy.random import randn
from time import time

def main():
    cpux = randn(2000, 2000).astype('float32')
    gpux = shared(cpux, 'x')
    gpu_mul = function(inputs=[], outputs=[], updates=[(gpux, gpux.dot(gpux))])
    start = time()
    gpu_mul()
    print "gpu multiply time: ", time() - start
    start = time()
    cpux = cpux.dot(cpux)
    print "cpu multiply time: ", time() - start
    print "diff: ", abs(gpux.get_value() - cpux).sum()

main()
