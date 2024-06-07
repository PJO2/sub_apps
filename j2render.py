#!/usr/bin/python3
import jinja2
import sys
import yaml
import argparse

# reads template and data file :
parser = argparse.ArgumentParser(prog = 'j2render', description='a basic jinja2 rendered')
parser.add_argument('-j', '--template', required=True,  help='the jinja2 template')
parser.add_argument('-y', '--data',     required=False, help='the data file in yaml')
args= parser.parse_args()

# read the template file
templateLoader = jinja2.FileSystemLoader(searchpath="./")
templateEnv = jinja2.Environment(loader=templateLoader)
template = templateEnv.get_template(args.template)

# read and resolev the yaml file
with open(args.data) as d:
    yaml_data = d.read()
values = yaml.safe_load(yaml_data)

outputText = template.render(values)  # this is where to put args to the template renderer

print(outputText)
