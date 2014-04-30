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
  - create a VCS hook (1 pt)
  - git cherry-pick, rebase (1 pt)


## Theory
  Working with CLI gave me a more general view on what is really happening aboug the work processes that sometimes is hidden or simplified by GUIs or IDEs. Working on a ssh server has its benefits. Most important is that it is remote. Main disatvantage is that it requires a connection(but nowadays it is not a big problem).
  Also, working with the Git VCS(as CL commands, not a GUI) showed me the purpose of such tools: tracking, recovering, teamwork etc.
  Vim is the very first CLI editor, and I find it very useful for small and rapid changes.

## Work

#####Create your own server (ex. virtual machine)
(on Mac OS) enable remote login:
````sh
systemsetup -setremotelogin on
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





  
  
