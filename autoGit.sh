#!/bin/bash
# Check status, pull, add, commit, check status, push, show log for git
clear
echo "Current status."
echo ""
git status
echo "Pulling latest code from github."
echo ""
git pull
echo "Adding files to commit."
echo ""
git add .
read -p "Please enter a commit message: " msg
echo ""
echo "Committing."
echo ""
git commit -m "$msg"
echo ""
echo "Pushing code to github"
echo ""
git push origin