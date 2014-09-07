import numpy
import theano
import theano.tensor as T

 
def theano_softmax():
    M = T.dmatrix("M")
    y = T.nnet.softmax(M)
    softmax_callable = theano.function([M], y)
    return softmax_callable
 
 
def theano_p_y_given_x():
    X = T.dmatrix('X')
    W = T.dmatrix('W')
    b = T.dmatrix('b')
    input = T.dot(X, W) + b
    y = T.nnet.softmax(input)
    p_y_callable = theano.function([X, W, b], y)
    return p_y_callable
 
 
def softmax(M):
    M = numpy.array(M)
    row_max = numpy.amax(M, axis=1)
    row_max = row_max.reshape(row_max.shape[0], 1)
    cwise_exp = numpy.exp(M - row_max)
    v_softmax = cwise_exp / numpy.sum(cwise_exp, axis=1).reshape(row_max.shape[0], 1)
    return v_softmax
 
def p_y_given_x(X, w, b):
    dt = numpy.dot(X, w) + b
    return softmax(dt)
 
