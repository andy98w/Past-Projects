import uproot
import pandas
import h5py
import numpy as np

def main():
    # File I/O
    iname = input("Path to input file: ")
    oname = input("Output file name (WITHOUT EXTENSION): ")
    of = uproot.open(iname)
    tree = of["Nominal"]
    
    # Select variables/keys to import
    variables = ['mJJ', 'cosThetaC', 'dRB1J1', 'cenPhJJ', 'pTJJ', 'pTBal', 'dEtaJJ', 'dRB1Ph', 'dPhiBBJJ', 'nJets', 'zep', 'etaJ5']
    select = input("What variables would you like to import (all/training/custom): ")
    
    if select == "custom":
        print("Variables\n--------")
        i = 1
        for k in tree.keys():
            print("{:22}| ".format(k), end = "")
            if(i % 4 == 0):
                print()
            i = i + 1
        s = input("\n\nEnter variables you would like to import separated by spaces\n--------\n")
        variables = s.split(" ")
    
    # Convert to pandas (DataFrame)
    print("Generating DataFrame, please wait...")
    df = tree.arrays(expressions=None, library = "pd") if select == "all" else tree.arrays(expressions=variables, library = "pd")
    print(df)
    
    # Create hdf file
    print("Creating hdf5 file...")
    df.to_hdf(oname + '.hdf5', key='df', mode='w')
    print("Success...")
    
    # Closing files
    print("Closing files...")
    of.close()
    
if __name__=="__main__":
    main()