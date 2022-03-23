## •	WHAT this project is about? 
This custom real time object detection detects a driver using cell phone while driving. Once the target object is detected, the image of the driver is taken and saved into the local storage. 


## •	WHY did I suggest this project idea for the Senior Design project?
Some people disliked the idea of "policing people". However, the reason why I suggested this idea is a little personal. Few years ago, my cousin died in a car accident. It was caused by a distracted driver nearby. I wanted to engineer something that would discourage distracted driving and hold the irresponsible drivers accountable. According to the National Safety Council, cell phone use while driving leads to 1.6 million crashes each year on average!!!


## •HOW did we make it? 
We used the SSD-MobilenetV2 architecture which was implemented with TensorFlow. We chose this architecure to help us train our model without having to use GPU. We gathered our own image data, and then used the ImageDataGenerator to augment and generate more images for both training and testing purposes. We then annotated the images with two different labels (classes) - "OnPhone" and "NotOnPhone" using labelImg. 







###### **Please feel free to visit the following site to check out more details, the presentation, and the demonstration!**

https://express.adobe.com/page/rNh1NAZyYFG9T/
