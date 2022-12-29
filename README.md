# EA_3 
## Environment
- OpenCV (4.6.0)
- MinGW (GCC 11.2.0)
- VScode
## How to use:

## Logs
Previous demostrate video: https://www.youtube.com/watch?v=AoP74Qt9JCE.
### 0.1.0
After EA class, I finally decided to develop a compact and easy-to-use evaluation system. Changes are:
- Use **Cmakefiles** to construct the project.
    - Compatible to different platform
    - Easy to manage dlls on Windows
- Use **OpenCV** to visualize images instead of freeglut.
    - OpenCV now has high efficient GPU methods.
    - Basic drawings of OpenCV are much more easier.
    - The evaluation process can directly exported as .mp4
    - OpenCV have computer vision functions, which will be used in future works.
- Put all evolution-related codes into subproject **Dao（道）**
    - Dao defines all the evolution features like population, cross over and selection in abstract class.
    - Dao defines all the math functions.
    - Dao defines utility functions
- **Application** folder contains different applications using Dao as a evolution library.