#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Script used to transfer Umeng's markdown file
# to github flavored html, and wrap it with css  
# 
# prerequisite:
    # python: http://www.python.org/getit/
    # python markdown package: https://pypi.python.org/pypi/Markdown
# usage:
    # python markdown2html.py foo.md

import os, sys
import markdown
import codecs

# hacked from python-markdown libary,
# since it doesn't support preceeding 
# by space, suck!
from fenced_code import FencedCodeExtension

# python encoding, really suck
ENCODING = 'utf-8'
CH_ENCODING = 'utf-8'

reload(sys)
sys.setdefaultencoding(ENCODING)

# css used to render transfered html
CSS = '<link rel="stylesheet" type="text/css" href="markdown.css"></link>'
htmlHead = '<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>'+CSS+'</head><body>'
htmlEnd = '</body></html>'
# githup flavored markdown extentions, 
# used to render github styled syntex blocks
EXTENTIONS = [FencedCodeExtension(), 'tables']

markdown.Extension.config = {}

# check existence of css script.
# the script will not excute till css is put 
# under the same directory with markdown file.
def checkcss(md_name):
    path, md_name = os.path.split(md_name)
    css = os.path.join(path, 'markdown.css')
    return os.path.isfile(css)

# transfer markdown to html.
# pay attention to githup flavored extentions.
def md2html(md_name):  
    md_file = open(md_name)
    md_text = md_file.read()
    md_text = unicode(md_text, ENCODING)
    md_file.close()

    #md_html = markdown2.markdown(md_text, extras=EXTENTIONS)
    md_html = markdown.markdown(md_text, EXTENTIONS) 
    md_html = md_html.encode(ENCODING).strip()
    return md_html

# save html file as well as append css.
def save2html(md_name, md_html):
    path, md_name = os.path.split(md_name)
    html_name = os.path.join(path, md_name.replace('md', 'html'))
    html_file = codecs.open(html_name, 'w', CH_ENCODING)
    html_file.write(htmlHead + os.linesep + htmlEnd)
    html_file.write(md_html)
    html_file.close()

# given a markdown file, save it to html file
def processone(md_name):
    if not (os.path.isfile(md_name) and md_name.endswith('.md')):
        print 'not a markdown file'

    md_content = md2html(md_name)
    save2html(md_name, md_content)

# give a directory, save all the markdown files
# to html files
def processmulti(md_dir):
    for f in os.listdir(md_dir):
        if f.endswith('.md'):
            md = os.path.join(md_dir, f)
            processone(md)
            print 'processed %s' % md

if __name__ == '__main__':
    md_name = sys.argv[1]
    md_css = None
    if len(sys.argv)> 2:
        md_css = sys.argv[2]

    if os.path.isfile(md_name):
        if md_css == None and not checkcss(md_name):
            print 'no css file!'
            sys.exit() 
        processone(md_name)
    elif os.path.isdir(md_name):
        processmulti(md_name)
    else:
        print 'can not recognize file or directory'
