import numpy as np
import cv2
import sys

dir_interpolated = './data/interpolated/'

def psnr(img1, img2):
    mse = np.mean((img1 - img2) ** 2)
    if mse == 0:
        return 100
    PIXEL_MAX = 255.0
    return 20 * np.log10(PIXEL_MAX / np.sqrt(mse))

if __name__ == '__main__':
    # ARGUMENTS: number of the label
    if len(sys.argv) == 2:
        filename_gt = f'./data/ground_truth/{sys.argv[1]}.png'
        filename_interpolated = './memoutput.png'
    else:
        # ERROR
        print('Usage: python psnr.py <label>')
        sys.exit(1)
        
    img_gt = cv2.imread(filename_gt, cv2.IMREAD_GRAYSCALE)
    img_interpolated = cv2.imread(filename_interpolated, cv2.IMREAD_GRAYSCALE)
    print(f'{sys.argv[1]}: {psnr(img_gt, img_interpolated)}')
    print('Done.')
    