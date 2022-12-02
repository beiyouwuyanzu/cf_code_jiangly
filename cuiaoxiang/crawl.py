from lxml import etree
import requests
import os
import time
import random
from datetime import datetime
import glob


start = 0
end = 50


def setDir(filepath):
    '''
    如果文件夹不存在就创建，如果文件存在就清空！
    :param filepath:需要创建的文件夹路径
    :return:
    '''
    if not os.path.exists(filepath):
        os.mkdir(filepath)




def crawl_single(url):
    singe_code = requests.get(url)
    page = etree.HTML(singe_code.text)
    # print(singe_code.text)
    code = page.xpath('//*[@id="program-source-text"]')
    # print(etree.tostring(code[0]))
    if not code:
        print("no code")
        return
    code = code[0].text.replace('\n\n\n', '//ENTER').replace('\n\n', '').replace('//ENTER', '\n\n')
    detail = page.xpath('//*[@id="pageContent"]/div[2]/div[6]/table/tr[2]/td[3]')
    # print(etree.tostring(detail[0]))
    # print(detail[0][0].text)
    q_url = "https://codeforces.com" + detail[0][0].get('href')
    name = detail[0][0].get('title').replace(' ', '')
    detail = detail[0][0].text
    round = detail[:-1]


    tm = page.xpath('//*[@id="pageContent"]/div[2]/div[6]/table/tr[2]/td[8]')[0].text
    print(tm, q_url, detail, name, round)
    dr = f'./{round}'
    fname = detail + "-" + name
    fname = fname.replace('/', '')
    print(dr, fname)
    if os.path.exists(dr + '/' + fname + ".cpp"):
        print("already exists, continue")
        return
    setDir(dr)
    code = f'// url:{q_url}\n// time:{tm}\n// name:{name}\n\n{code}'
    with open(dr + '/' + fname + '.cpp', 'w') as f:
        f.write(code + '\n')






for i in range(start, end):


    print("\n" * 2)
    print(datetime.now())
    print("\n" * 2)
    page_index = f"https://codeforces.com/submissions/cuiaoxiang/page/{i}"
    page_index_res = requests.get(page_index).text
    # print(page_index_res)
    html = etree.HTML(page_index_res)


    # print(html)
    tmp_page = html.xpath('//*[@id="pageContent"]/div[4]/div[6]/table/tr')
    # print(type(tmp_page[0]))
    # print(tmp_page.get('href'))
    for x in tmp_page[1:]:
        #print(etree.tostring(x[0]))
        # print(x.get('href'))
        intro = x[3][0].get('href')
        if intro.count('/') == 4:
            _, _, num, _, tag = intro.split('/')
        else:
            num = "xxx"
            tag = "yyy"


        if glob.glob(f"./*{num}*/*{num}*{tag}*"):
            print(f"{num} {tag} aleady download. continue")
            continue


        info = etree.tostring(x[0])
        sta = x[5].findall('span/span')
        if sta:
            sta = sta[0].text.strip()


        if sta == "Accepted":
            if not x[0].findall('a'):
                continue
            hf = x[0].findall('a')[0].get('href')
            url = 'https://codeforces.com' + hf
            print(url)
            crawl_single(url)
            time.sleep(random.uniform(0,2))
