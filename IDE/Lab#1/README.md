# IDE Laboratory Work #1

## Subject

Command Line Interface; CLI Editors; Setting Server Environment; Version Control Systems

## Objectives:
  - Understanding and using CLI (basic level)
  - Administration of a remote linux machine using SSH
  - Ability to work remotely (remote code editing)
  - Ability to work with VCS

## Done Tasks:
**Mandatory Tasks:**
  - connect to a remote server via SSH;
  - initialize a repository on server;
  - create a file in repository folder, write in your name, save it and commit it.

**Tasks With Points:**
  - create an ssh server (2 pt)
  - connect to server using public key (1 pt)
  - create 2 more branches with at least one unique committed file per branch (1 pt)
  - set a branch to track a remote origin on which you are able to push (ex. github, bitbucket or a custom server) (1 pt)
  - create a VCS alias (1 pt)
  - Create a VCS merge conflict and solve it(1 pt)
  - git cherry-pick, rebase (1 pt)


## Theory
  Working with CLI gave me a more general view on what is really happening aboug the work processes that sometimes is hidden or simplified by GUIs or IDEs. Working on a ssh server has its benefits. Most important is that it is remote. Main disatvantage is that it requires a connection(but nowadays it is not a big problem).
  Also, working with the Git VCS(as CL commands, not a GUI) showed me the purpose of such tools: tracking, recovering, teamwork etc.
  Vim is the very first CLI editor, and I find it very useful for small and rapid changes.

## Work

#####Create your own server (ex. virtual machine)
(on Mac OS) enable remote login:
````sh
sudo systemsetup -setremotelogin on
````

On iOS device using openSSH jailbreak tweak + setted on the device GIT VCS and Ruby. 
Connected via same WiFi network:
````sh
ssh root@192.168.0.3
password:
````

#####Connect to a remote server via SSH:

````sh
ssh username@server
````

#####Init a git repo:
````sh
git init
````

#####Create a file in repository folder, write in your name, save and commit it
````sh
   mkdir foldername
   touch filename.txt
   vim filename.txt                  
   i                             
   Name Surname              
   :wq                           
   git add filename.txt              
   git commit -m "Txt created"
````

#####Connect to server using public key
  - Creating a key:
  
  ````sh 
  ssh-keygen -t rsa
  ````

  - Adding created key to authorized list:
   ````sh
   cat ~/.ssh/id_rsa.pub | ssh user@ip "cat - >> ~/.ssh/authorized_keys"
   ````

#####Create 2 more branches with at least one unique committed file per branch
(in branch2 will be present both branch1.txt & branch2.txt)
````sh
    git branch branch1
    git checkout branch1
    touch branch1.txt        
    git add branch1.txt      
    git commit -m 'commit branch1'
    git branch branch2
    git checkout branch12
    touch branch2.txt        
    git add branch2.txt      
    git commit -m 'commit branch2'
````
  
#####Reset a branch to previous/specific commit and restore

  - Reset to previous:
  `git reset --hard HEAD`

  - Reset to specific(ID got from history log): 
  `git reset --hard ID`

  - Restore(quick)
  ````sh
   git reflog          
   git reset --hard ID
  ````


#####Make your CLI text editor to highlight code, in my case Vim:
Just used the switch of its built-in highlither:
`syntax on`

#####Create a VCS alias, in my case Git:
Found and set some useful aliases:
````sh
git config --global alias.st 'status'
git config --global alias.hist 'log --pretty=format:"%h %ad | %s%d [%an]" --graph --date=short'
````

#####Master any CLI editor, in my case Vim.

- `all` - Begin a new line above the cursor and insert text

- `ggguG` - lowercase all text

- `o` - Begin a new line below the cursor and insert text

- `/word` - search word from top to bottom

- `?word` - search word from bottom to top

- `:%s/$/word/g` - add word at the end of each line

- `:%s/word1/word2/g` - replace word1  by word2 in all  the file

- `:g/word/d`  - delete all lines containing word

- `Ctrl+n ,Ctrl+p` - Auto-complete

- `:Sex` - Split window and open integrated file explorer

- `:args` - list files

- `:ls` - list buffers


#####Create a VCS merge conflict and solve it
Conflict: Edited a file in two different branches and try to merge them.
Used method for branch creation as above then:
`git merge branch2`

- Result:
````sh
U   branch1.txt
fatal: 'commit' is not possible because you have unmerged files.
Please, fix them up in the work tree, and then use 'git add/rm ' as appropriate to mark resolution and make a commit, or use 'git commit -a'.
````
- Solving: 
Opened with `vim branch1.txt` and chosed what I want to edit, then:
`git commit -a -m 'commit name'`

#####Cherry-pick and rebase
Using same branches branch1 and branch2:
```` sh
git checkout -b branch3
touch brahch3.txt
git add brahch3.txt
git commit -a -m "commitName"
git checkout branch2
git rebase branch1      #branch1->branch2
git cherry-pick branch3 # apply last commit of branch3 to the current one
````


  
  
