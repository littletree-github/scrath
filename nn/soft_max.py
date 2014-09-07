#!/usr/bin/env python

import numpy
import theano
import theano.tensor as T
import os


def generate_theano_softmax():
    M = T.matrix("M")
    y = T.nnet.softmax(M)
    softmax_callable = theano.function([M], y)
    return softmax_callable
 
theano_softmax = generate_theano_softmax()
 
def generate_theano_p_y_given_x():
    X = T.matrix('X')
    W = T.matrix('W')
    b = T.matrix('b')
    y = T.nnet.softmax(T.dot(X, W) + b)
    p_y_callable = theano.function([X, W, b], y)
    return p_y_callable

theano_p_y_given_x = generate_theano_p_y_given_x()


def generate_theano_predict():
    X = T.matrix('X')
    W = T.matrix('W')
    b = T.matrix('b')
    y = T.nnet.softmax(T.dot(X, W) + b)
    y_pred = T.argmax(y, axis=1)
    return theano.function([X, W, b], y_pred)

theano_predict = generate_theano_predict()


def softmax(M):
    M = numpy.array(M)
    row_max = numpy.amax(M, axis=1)
    row_max = row_max.reshape(row_max.shape[0], 1)
    cwise_exp = numpy.exp(M - row_max)
    v_softmax = cwise_exp / numpy.sum(cwise_exp, axis=1).reshape(row_max.shape[0], 1)
    return v_softmax


def p_y_given_x(X, W, b):
    dt = numpy.dot(X, W) + b
    return softmax(dt)
 
def predict(X, W, b):
    y = p_y_given_x(X, W, b)
    return numpy.argmax(y, axis=1)


