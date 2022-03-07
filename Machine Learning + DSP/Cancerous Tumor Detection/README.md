### **Introduction:** 

  It goes without saying how machine learning is a heavily researched field today. And there is a good reason why. Machine learning has proven itself as a magical tool - it is amazing to see what a bunch of numbers in the form of clean data can do. This is the reason why I wanted to do a project which could have a popularity in its application. This project is about determining if the benign colon tumor is cancerous or not. Using SVM to do MNIST digit classification has been quite popular for some time. This inspired me to do the same, but instead, with the jpeg format images of the MRI images of benign colon tumor.

### **Dataset:** 

  https://academictorrents.com/details/7a638ed187a6180fd6e464b3666a6ea0499af4af

### **Target Labels:**
  **Class 0:** Tumor is cancerous. 
  **Class 1:** Tumor is not cancerous 


### **Method:** 
  1) Reduced the data features from 589824 to 2976 using Principal Component Analysis with n_components = 0.9 
   ###### 0.9 = variance ratio
  

  ![02](https://user-images.githubusercontent.com/80914380/156063027-6856129d-ce12-493a-b308-0eb4f95ce616.JPG)



  ![03](https://user-images.githubusercontent.com/80914380/156063051-411e477f-189f-4a33-a3d3-9c05d2631a2b.JPG)

  2) Used the RBF Kernel of SVM to classify the images into two classes - cancerous and non-cancerous. 
  #### RBF = Radial Basis Function with gamma = "scale" ( = 1 / (n_features * X.var()))
 
 
## **Accuracy = 94%** 



![01](https://user-images.githubusercontent.com/80914380/156063173-b31e01c6-5260-4e99-92d9-ebe3e253608e.JPG)
