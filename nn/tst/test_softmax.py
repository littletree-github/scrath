from numpy.random import randn
from numpy.random import seed
from numpy import allclose
from .. import soft_max
from nose.tools import ok_
 
def test_soft_max():
    seed(12345)
    X = randn(10, 10) 
    w = randn(10, 10)
    b = randn(10, 10)
    smx_th = soft_max.theano_softmax()(X)
    smx = soft_max.softmax(X)
    
    ok_(allclose(smx_th, smx), "theano and numpy softmax should generate same result for same input")
    th_py = soft_max.theano_p_y_given_x()(X, w, b)
    py = soft_max.p_y_given_x(X, w, b)
    ok_(allclose(th_py, py), "theano and numpy softmax should generate same proba for same input")


