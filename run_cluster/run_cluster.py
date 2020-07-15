#!/bin/sh
# coding: utf-8
'''':
# Upgrade no more than once a day
if test -n "$(find $0 -mtime +1)"; then
    pip3 install --user --upgrade pip
    pip3 install --user --upgrade pandas numpy
    touch $0
fi
exec python3 $0 $@
'''
from __future__ import print_function

import argparse
import errno
import itertools
import os
import os.path
import re
import sys
import pandas as pd
import toml
import subprocess
from collections import OrderedDict

named_options = {
}

from itertools import zip_longest

def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)

def flatten(l):
    """Flatten one level of lists"""
    r = []
    for i in l:
        if type(i) is list:
            r += i
        else:
            r.append(i)
    return r

def expand_named_option(opt):
    return opt if opt.startswith("-") else named_options[opt]

def expand_named_options(l):
    res = []
    for k in l:
        opts = ' '.join(expand_named_option(k) for k in l[k])
        res.append((k, opts))
    return res

def changedir(directory):
    """Change directory, creating it if it does not exist."""
    try:
        os.makedirs(directory)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise
    os.chdir(directory)

def opt(x, f):
    return zip(x, map(f, x))

def createStr(x):
    s = "00000"
    sx = str(x)
    return s[0:5-len(sx)]+sx

def submit_jobs(config, regex=None, execute=False):
    kek = [r for r in range(1,11)]
    runs = opt(kek, lambda x: '{}'.format(x))
    isd = opt(config['range'], lambda x: config['range_format'].format(x))

    if 'options' in config:
        for k, v in config['options'].items():
            named_options[k] = v

    case_params = [named_options[k] for k in config['constants']]
    variables = map(expand_named_options, config['variables'])

    condor_submit_args = ['condor_submit', '-disable', '-single-cluster']
    if not execute:
        condor_submit_args += ['-dry-run', '-']
    condor_submit_args += ['-'] # read from stdin



    for g in grouper(itertools.product(runs), 20000):
        process = subprocess.Popen(condor_submit_args,
                            stdin=subprocess.PIPE,
                            stdout=subprocess.PIPE,
                            #stderr=subprocess.PIPE,
                            encoding='utf-8')

        condor_submit_input = f'''\
executable = ../../main
JobBatchName = music
'''
        i = 0;
        for t in g:
            if not t:
                continue
            base = 'music_'+'-'.join(map(str, list(zip(*t))[0]))

            if os.path.isfile(base + '.log'):
                # Do not schedule one job twice.
                continue

            if regex and not regex.match(base):
                continue
            opts = list(list(zip(*t))[1])

            args = flatten(opts)
            files = ["../../../../music/experiment/winner_csi/csi_"+createStr(kek[i])+".txt"]
            i += 1
            args  = [s for s in args if not s.startswith('file:')]

            print(base)
            condor_submit_input += f'''
rank = (SlotId)
log = {base}.log
output = {base}.out
error = {base}.err
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = {", ".join(files)}
transfer_output_files = {base}
arguments = {" ".join(args)}
'''

            if 'ClusterOnly' in config and config['ClusterOnly']:
                condor_submit_input += '''\
requirements = (TARGET.TotalSlots < 37) && (TARGET.TotalSlots > 16)
'''
            condor_submit_input += '''\
queue
'''

        print(condor_submit_input)

        outs, errs = process.communicate(input=condor_submit_input)

def get_arguments():
    parser = argparse.ArgumentParser(description='Schedule HTCondor jobs')
    parser.add_argument('-x', help='Actually submit jobs', action='store_true')
    parser.add_argument('--filter', type=str)
    parser.add_argument('--summary', action='store_true')
    parser.add_argument('config', help='configuration file')
    return parser.parse_args()

def main():
    args = get_arguments()
    config = toml.load(args.config, _dict=OrderedDict)

    changedir(os.path.join(config['scenario'], 'results', config['name']))

    regex = re.compile(args.filter) if args.filter else None
    submit_jobs(config, regex=regex, execute=args.x)

if __name__ == '__main__':
    main()
