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

# css used to render transfered html
CSS = '<link rel="stylesheet" type="text/css" href="markdown.css"></link>'
htmlHead = '<html><head><meta http-equiv="Content-Type" content="text/html;     charset=utf-8"/>'+CSS+'</head><body>'
htmlEnd = '</body></html>'
# python encoding, really suck
ENCODING = 'utf-8'

# githup flavored markdown extentions, 
# used to render github styled syntex blocks
EXTENTIONS = ['fenced_code', 'tables']

# check existence of css script.
# the script will not excute till css is put 
# under the same directory with markdown file.
def checkcss(md_name):
    path, md_name = os.path.split(md_name)
    css = os.path.join(path, 'markdown.css')
    print css
    return os.path.isfile(css)

# transfer markdown to html.
# pay attention to githup flavored extentions.
def md2html(md_name):  
    md_file = open(md_name)
    md_text = md_file.read()
    md_text = unicode(md_text, ENCODING)
    md_file.close()

    md_html = markdown.markdown(md_text, EXTENTIONS) 
    md_html = md_html.encode(ENCODING).strip()
    return md_html

# save html file as well as append css.
def save2html(md_name, md_html):
    path, md_name = os.path.split(md_name)
    html_name = os.path.join(path, md_name.replace('md', 'html'))
    html_file = open(html_name, 'w')
    html_file.write(htmlHead + os.linesep)
    html_file.write(md_html)
    html_file.write(htmlEnd)
    html_file.close()

if __name__ == '__main__':
    md_name = sys.argv[1]
    if not checkcss(md_name):
        print 'no css file!'
        sys.exit()

    md_content = md2html(md_name)
    save2html(md_name, md_content)
    

