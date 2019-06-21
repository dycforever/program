import os
import sys
import time
#import cv2
# import tensorflow as tf
import base64
import urllib
from urllib import request
import json
import numpy as np
# from PIL import Image
import random

def safe_download(image_url, time_out, gif_is_not_good=True):
    try:
        t_s_urlopen = time.time()
        resp_file = urllib.request.urlopen(image_url, timeout=time_out)
        print('time spend on open url ', time.time()-t_s_urlopen)
        cio = Image.io.BytesIO()
        im = Image.open(Image.io.BytesIO(resp_file.read()))
        print('time spend on open im ', time.time()-t_s_urlopen)
        if 1.0*im.size[0]/im.size[1]>3 or 1.0*im.size[0]/im.size[1]<0.3:
            return np.zeros((1,1)), False
        imtype = im.format.upper()
        im.convert('RGB').save(cio, format='JPEG', quality=100)
        print('time spend on convert ', time.time()-t_s_urlopen)
        img_c = cio.getvalue()
        print('time spend on getvalue ', time.time()-t_s_urlopen)
        cio.close()
        if imtype == 'GIF' and gif_is_not_good:
            return img_c, False
        else:
            return img_c, True
    except Exception as err:
        exc_type, exc_obj, exc_tb = sys.exc_info()
        fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
        print(exc_type, fname, exc_tb.tb_lineno)
        print('img {} download error'.format(image_url, err))
        return np.zeros((1,1)), False

def softmax(x):
    """Compute softmax values for each sets of scores in x."""
    # e_x = np.exp(x - np.max(x))
    # return e_x / e_x.sum()
    return np.exp(x) / np.sum(np.exp(x), axis=0)

# img = cv2.imread('16.jpg')

def make_request(img_bin):
    img_encode = base64.urlsafe_b64encode(img_bin)

    single_request_str = '[|]\nimage_content=0:{}'.format(img_encode)

    request_str = ''
    for i in range(0):
        request_str = request_str + single_request_str + '\n'
    request_str = request_str + single_request_str

    #server_ip = "http://11.9.89.27:4780/video_image_clarity_4_labels_export"
    server_ip = "http://{}/video_image_clarity_4labels_32batchsize".format(random_ip)
    server_ip = "http://{}/mini_video_clarity_4_label_test".format(random_ip)
    server_ip = "http://11.9.21.41:5660/watermark_v1"
    server_ip = "http://{}/watermark_v1".format(random_ip)
    server_ip = "http://{}/poster_cropper_ranker_v0_2".format(random_ip)
    server_ip = "http://{}/yolo_test_single".format(random_ip)
    server_ip = "http://tensorflow_yolov3.zeus.vipserver:7867/tensorflow_yolov3"
    #server_ip = "http://sm_tfs_yolo_eu95_test.vipserver:4968/yolo_test_single"
    #server_ip = 'http://sm_tfs_video_image_clarity_service_online.vipserver:5492/video_image_clarity_label_4_online'
    t_s_req = time.time()
    for i in range(300):
        t_s_req_1 = time.time()
        server_res = request.urlopen(request.Request(url=server_ip,data=request_str)).read()
        t_e_req_1 = time.time()
        print(t_e_req_1-t_s_req_1)
    t_e_req = time.time()
    fout = open('fout.txt', 'w')
    fout.write(server_res)
    print('end of zeus', t_e_req-t_s_req)

    ###### eu95 test
    server_ip = "http://sm_tfs_yolo_eu95_test.vipserver:4968/yolo_test_single"
    t_s_req = time.time()
    for i in range(300):
        t_s_req_1 = time.time()
        server_res = request.urlopen(request.Request(url=server_ip,data=request_str)).read()
        t_e_req_1 = time.time()
        print(t_e_req_1-t_s_req_1)
    t_e_req = time.time()
    fout = open('fout.txt', 'a')
    fout.write(server_res)
    print('end of eu95', t_e_req-t_s_req)


    fc_res = np.array(json.loads(server_res)['output']['content'])
    result = softmax(fc_res).tolist()
    print('fc_res ', fc_res, type(fc_res))
    print('final result ', result, type(result), 'time', t_e_req-t_s_req)



#img_bin = open('16.jpg', 'rb').read()

VIPPARSER = 'http://172.18.55.120/vipserver/api/srvIP'
domain = 'sm_tfs_video_image_clarity_service_online.vipserver'
domain = 'sm_tfs_video_image_clarity_for_poster_slector.vipserver'
domain = 'sm_tfs_mini_video_clarity_4_label_test.vipserver'
domain = 'sm_tfs_watermark_v1_test.vipserver'
domain = 'sm_tfs_yolo_test.vipserver'
cluster = 'eu95'
cluster = 'shenma-test'

domain = 'sm_tfs_poster_cropper_ranker_v0_2_test.vipserver'
cluster = 'eu95'

domain = 'sm_tfs_yolo_eu95_test.vipserver'
cluster = 'eu95'

response = request.urlopen(request.Request('{}?dom={}&clusters={}'.format(VIPPARSER, domain, cluster))).read()
print(json.loads(response)['ips'])
print(len(json.loads(response)['ips']))
for ips in json.loads(response)['ips']:
    #print ips
    pass
random_ip = random.choice(json.loads(response)['ips'])
print(random_ip)

#os._exit(0)

img_url = sys.argv[2]
d_time = 1.5
img, status = safe_download(img_url, d_time)

if sys.argv[1] == 'local':
    img_array = cv2.imdecode(np.frombuffer(img, np.uint8), -1)
    cv2.imwrite('tmp.jpg', img_array)
    img_bin = open('tmp.jpg', 'rb').read()
    img_bin = img_bin
    make_request(img_bin)
elif sys.argv[1] == 'web':
    img_bin = img
    make_request(img_bin)

elif sys.argv[1] == 'both':
    img_array = cv2.imdecode(np.frombuffer(img, np.uint8), -1)
    cv2.imwrite('tmp.jpg', img_array)
    img_bin = open('tmp.jpg', 'rb').read()
    img_bin = img_bin
    make_request(img_bin)


    t_start_prepare = time.time()
    img_array = cv2.imdecode(np.frombuffer(img, np.uint8), -1)
    print('Finished prepare str to cv {}'.format(time.time()-t_start_prepare))
    #resized_img = cv2.resize(img_array, (500,500), interpolation=cv2.INTER_NEAREST)
    resized_img = cv2.resize(img_array, (428, 375), interpolation=cv2.INTER_CUBIC)
    #resized_img = cv2.resize(img_array, (500,500))
    print(resized_img.shape)
    print('resized_img shape ', resized_img.shape)
    print('Finished prepare resize {}'.format(time.time()-t_start_prepare))

    resized_pil = Image.fromarray(resized_img.astype('uint8')).convert('RGB')
    print('Finished prepare pil {}'.format(time.time()-t_start_prepare))

    imgByteArr = Image.io.BytesIO()     #build an empty bytes object
    resized_pil.save(imgByteArr, format='JPEG') # save pil image as jpeg
    imgByteArr = imgByteArr.getvalue()   # get the value of bytes string
    print('Finished prepare str {}'.format(time.time()-t_start_prepare))


    img_bin = imgByteArr
    make_request(img_bin)


    imgByteArr = Image.io.BytesIO()     #build an empty bytes object
    resized_pil.save(imgByteArr, format='PNG') # save pil image as jpeg
    imgByteArr = imgByteArr.getvalue()   # get the value of bytes string
    print('Finished prepare str {}'.format(time.time()-t_start_prepare))


    img_bin = img
    for i in range(1):
        make_request(img_bin)



