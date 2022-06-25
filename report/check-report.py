import json
import sys
import os
import re


report_filename = 'report.json'

def abort(message):
    print(f'ERROR: {message}')
    sys.exit(-1)

def check_first_name(value):
    if not isinstance(value, str):
        abort('first-name should be string')
    if value == 'TODO':
        abort('Oh come on, you forgot to fill in your first name!')

def check_last_name(value):
    if not isinstance(value, str):
        abort('last-name should be string')
    if value == 'TODO':
        abort('... You forgot to fill in your last name')

def check_url(value):
    if not isinstance(value, str):
        abort('github-url should be string')
    if not re.fullmatch(r'https://github.com/ucll-pvm2122/huffman-([^./]*)', value):
        abort('github-url is invalid; it should have the form https://github.com/ucll-pvm2122/huffman-LOGIN')


print(f"Looking for {report_filename}")
if not os.path.isfile(report_filename):
    abort(f"Failed to find {report_filename}")

print(f"Opening {report_filename}...")
with open(report_filename) as file:
    print(f"Parsing JSON...")
    try:
        data = json.load(file)
    except:
        abort(f"Failed to parse JSON file")

print("Checking contents...")

for key, checker in [ ('first-name', check_first_name), ('last-name', check_last_name), ('github-url', check_url) ]:
    if key not in data:
        abort(f'Missing {key}')
    value = data[key]
    checker(value)



print('SUCCESS')
print('You can upload your report now')
print('Note: approval of this script does NOT mean your report.json is necessarily fully correct')
print('For example, your name or GitHub URL could still be wrong; there is no way for this script to check this')