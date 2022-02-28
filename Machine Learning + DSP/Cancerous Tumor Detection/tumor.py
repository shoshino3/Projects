# -*- coding: utf-8 -*-
"""
Created on Sat Apr 24 00:13:33 2021

@author: kajim
"""



import cv2
import glob
import numpy as np
#import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn import svm
from sklearn import metrics
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, ConfusionMatrixDisplay
#from sklearn.metrics import plot_confusion_matrix
from sklearn.metrics import confusion_matrix
import joblib
from joblib import dump, load

import pickle as pk


def read_img(img_list, img):
    n = cv2.imread(img, 0)
    img_list.append(n)
    return img_list



def dim_reduce(batch_x):
    
    
    
   print(np.shape(batch_x))
    
   inc_pca = PCA(n_components = 0.9) 
    
    
       
    
   inc_pca.fit_transform(batch_x)
   pk.dump(inc_pca, open("pca.pkl","wb"))
    
    """
    with open('pca.pkl', 'rb') as pickle_file:
            pca = pk.load(pickle_file)
    """
    #inc_pca = pk.load(open("pca.pkl",'rb'))

    X_reduced =inc_pca.fit_transform(batch_x)
    
    

    return X_reduced




path_batch = glob.glob('Training/*.jpeg')
list_batch = []

print("..reading data.... ")
cv_image_batch = [read_img(list_batch, img) for img in path_batch]
batch_X = np.asarray(list_batch, dtype=np.float32) #data type is array
batch_X_arr = batch_X.reshape(len(batch_X),-1)

print("reducing dimensions now.... ")
print(np.shape(batch_X_arr))
img_array_batch_red = dim_reduce(batch_X_arr)  #using Incremental PCA to reduce dimensions
batch_X= img_array_batch_red/255.0 

batch_Y_arr = np.zeros(7998)

for i in range(0,3999):
    batch_Y_arr[i] = 0
for i in range(4000,7998):
    batch_Y_arr[i] = 1

print("..splitting data... ")

X_train, X_test, Y_train, Y_test = train_test_split(batch_X, batch_Y_arr, shuffle = True, test_size=0.25)

print(np.shape(X_train))
print(np.shape(Y_train))

print(np.shape(X_test))
print(np.shape(Y_test))

""" training """" 
print("training started....")
clf = svm.SVC(kernel='rbf', gamma = "scale" ,C= 1) # compiling model
clf.fit(X_train, Y_train) #Train the model using the training sets
dump(clf,'saved_weights.joblib')  #saving the vector
print("training done...")


""" testing """
print("Now testing....")

clf_svm = load('saved_weights.joblib') #loading the vector
y_pred = clf_svm.predict(X_test) #Predict the response for test dataset
    



""" metrics """

print("Accuracy:\n")
scores = metrics.accuracy_score(Y_test, y_pred)
print(scores)
print("\n")
print("Classification report:\n")
print(classification_report(Y_test ,y_pred))
print("\n")
print("Confusion Matrix:\n")

cm = confusion_matrix(Y_test, y_pred, labels=clf_svm.classes_)
disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=clf_svm.classes_)
disp.plot()






