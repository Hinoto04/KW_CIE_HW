import array
import struct
from PIL import Image
import numpy as np

width, height = 80, 80

def ieee754_to_float(hex_str):
    try:
        temp = ""
        temp += hex_str[6:]
        temp += hex_str[4:6]
        temp += hex_str[2:4]
        temp += hex_str[0:2]
        hex_str = temp
        value = int(hex_str, 16)
        float_value = struct.unpack('!f', struct.pack('!I', value))[0]
        # Clip to 0-255 range
        if float_value < 0:
            float_value = 0
        elif float_value > 255:
            float_value = 255
        return int(float_value)
    except:
        return 0

def hex2image(hexfile, outfile):
    with open(hexfile, 'r') as f:
        lines = f.readlines()
    
    # Remove header line
    lines.pop(0)
    # Remove first and last 3 lines
    lines = lines[1:-3]
    # Remove address and checksum
    lines = [line[9:-3].strip() for line in lines]
    # Join all lines
    hex_data = ''.join(lines)
    
    # Create numpy array for the image
    img_array = np.zeros((height, width), dtype=np.uint8)
    
    # Process 4 bytes (8 hex chars) at a time for IEEE 754
    for i in range(width * height):
        if i*8 + 8 <= len(hex_data):
            hex_value = hex_data[i*8:i*8+8]
            pixel_value = ieee754_to_float(hex_value)
            
            # Set pixel value
            y = i // width
            x = i % width
            img_array[y, x] = pixel_value
    
    # Convert to PIL Image
    img = Image.fromarray(img_array)
    # Save as PNG
    img.save(outfile)

if __name__ == '__main__':
    hex2image('memoutput.hex', 'memoutput.png')
    print('Done!')
