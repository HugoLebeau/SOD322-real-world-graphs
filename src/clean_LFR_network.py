import argparse
import pandas as pd

parser = argparse.ArgumentParser()
parser.add_argument('--file', type=str, metavar="FILE")
args = parser.parse_args()

df = pd.read_csv(args.file, sep='\t', skiprows=1, header=None)
df[[0, 1]].to_csv(args.file, sep=' ', header=False, index=False)
