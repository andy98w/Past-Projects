# Nautilus ML

Jupyter-based ML on the Nautilus hypercluster with TensorFlow, Keras, and scikit-learn

Log on at https://jupyterhub-west.nrp-nautilus.io/

## Getting the repository onto computer

1. Enter ```ssh-keygen``` into terminal
2. Press enter until the key is generated
3. Enter ```cat ~/.ssh/id_rsa.pub``` to output contents of the public key into terminal
4. Copy key starting from "ssh-rsa" until end of line
5. Go on github/gitlab and enter public key into account's SSH Keys
    - GitHub: Settings -> SSH and GPG keys -> New SSH key
    - GitLab: Preferences -> SSH keys
6. Go back to workspace terminal and enter ```git clone git@git.ucsc.edu:scipp-atlas-higgs/nautilus-ml.git``` into repository of your choice
    - If a warning appears stating you have an unprotected private key file, enter ```chmod 700 ~/.ssh/id_rsa``` into terminal

## Setting up the workspace

1. Enter ```chmod +x setup.sh``` into terminal while in the directory
2. Enter ```./setup.sh``` into terminal to run script

## Generating hdf5 files

Run ```python generate.py``` and follow the instructions

## Miscellaneous

Background:
http://scipp.ucsc.edu/~nielsen/bb/344180ade_cgeeMaker.root

Higgs Boson Signal:
http://scipp.ucsc.edu/~nielsen/bb/346485ade_cgeeMaker.root

Variables for training:
```
mJJ, cosThetaC, dRB1J1, cenPhJJ, pTJJ, pTBal, dEtaJJ, 
dRB1Ph, dPhiBBJJ, nJets, zep, etaJ5
```
MJ1 was not found in the background ROOT and higgs ROOT files.

For the GWVersionTryMachineLearning file, need background variables as 'background.hdf5' and higgs variables as 'higgs.hdf5'

Add new variable to classify between Higgs and Background
(12 -> 13) variables

Change density last layer to 2 or 1 to verify whether it is Higgs or Background

Test accuracy, use binary classifier