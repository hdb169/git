# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

source /etc/profile.d/modules.sh
source /site/env/sysprofile

pathprepend() {
  for ((i=$#; i>0; i--)); 
  do
    ARG=${!i}
    if [ -d "$ARG" ] && [[ ":$PATH:" != *":$ARG:"* ]]; then
      PATH="$ARG${PATH:+":$PATH"}"
    fi
  done
} 
pathappend() {
  for ARG in "$@"
  do
    if [ -d "$ARG" ] && [[ ":$PATH:" != *":$ARG:"* ]]; then
      PATH="${PATH:+"$PATH:"}$ARG"
    fi
  done
}

#export TERM="xterm-256color"
export LANG=en_US.utf8

# If not running interactively, don't do anything
#[ -z "$PS1" ] && return

# don't put duplicate lines in the history. See bash(1) for more options
export HISTCONTROL=ignoredups

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

running_singularity=
if [ -e /.singularity.d/runscript ] ; then
  running_singularity="\#singularity"
fi
# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
xterm-256color)
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]${running_singularity}\$ '
    ;;
screen-256color)
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]${running_singularity}\$ '
    ;;
xterm)
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]${running_singularity}\$ '
    ;;
xterm-color)
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]${running_singularity}\$ '
    ;;
*)
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w${running_singularity}\$ '
    ;;
esac

# Comment in the above and uncomment this below for a color prompt
#PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PROMPT_COMMAND='echo -ne "\033]0;${USER}@${HOSTNAME}: ${PWD/$HOME/~}\007"'
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ "$TERM" != "dumb" ]; then
    eval "`dircolors -b`"
    alias ls='ls --color=auto'
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
fi

# Less Colors for Man Pages
export LESS_TERMCAP_mb=$'\E[01;31m'       # begin blinking
export LESS_TERMCAP_md=$'\E[01;38;5;74m'  # begin bold
export LESS_TERMCAP_me=$'\E[0m'           # end mode
export LESS_TERMCAP_se=$'\E[0m'           # end standout-mode
export LESS_TERMCAP_so=$'\E[38;5;246m'    # begin standout-mode - info box
export LESS_TERMCAP_ue=$'\E[0m'           # end underline
export LESS_TERMCAP_us=$'\E[04;38;5;146m' # begin underline

#export GREP_OPTIONS='--color=auto'
export FC=gfortran
export EDITOR=vim
export VISUAL=vim
export GCC_COLORS=1

if [ -n "$DISPLAY" ]; then
   export BROWSER=firefox
else
   export BROWSER=links
fi


# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

export PATH=/usr/local/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/lib:/usr/local/lib64:$LD_LIBRARY_PATH


##########################################
# CUE SETUP
##########################################

if [[ ! -z ${running_singularity} ]] ; then
  echo running singluarity
fi

if [[ -z ${running_singularity} ]] ; then

  #____________ CentOS version config ______________
  kernel=`uname -r`  
  iscentos62=`uname -r | grep el6`
  #echo "iscentos=$iscentos62;"
  centosVersion=$(cat /etc/redhat-release)
  machinearch=`uname -m`
  echo "Running on ${machinearch}"

  # http proxy
  export https_proxy=https://jprox.jlab.org:8082
  export http_proxy=http://jprox.jlab.org:8081
  export ftp_proxy=ftp://jprox.jlab.org:8081

  #cernlib
  export CERN_ROOT=$HOME/lib/cernlib/2006

  # --------------------------------------------------------------------
  # python
  export PATH=$HOME/.local/bin:$PATH
  export PYTHONPATH=$HOME/.local/lib:$PYTHONPATH
  export LD_LIBRARY_PATH=$HOME/.local/lib:$LD_LIBRARY_PATH
  export MANPATH=$HOME/.local/man:$HOME/.local/share/man:$MANPATH


  # LaTeX 
  export TEXMFHOME=$HOME/.texmf
  export TEXINPUTS=.:$TEXINPUTS:$HOME/.texmf/:

  #export SINGULARITY_CACHEDIR=/work/xxxxxx/singularity_cache
  export PATH=${PATH}:${SINGULARITY_CACHEDIR}

  # MODULES
  modulepathappend() {
    for ARG in "$@"
    do
      if [ -d "$ARG" ] && [[ ":$MODULEPATH:" != *":$ARG:"* ]]; then
        MODULEPATH="${MODULEPATH:+"$MODULEPATH:"}$ARG"
      fi
    done
  }

  #module load singularity-2.5.2

  modulepathappend /group/c-csv/local/etc/modulefiles
  module load hallc_tools/latest
  module load hcana/latest
  module load csv/latest
  module load tmux/latest
  module load cmake/latest
  module load python/2.7.15
  module load root/latest
  module load git/latest
  module load gcc/latest
  module load epics/latest
  module load ncurses/6.1
  module load ruby/2.5.3


fi

# --------------------------------------------------------------------
# Home directory is always the first stop 
export PATH=$HOME/bin:$PATH
export LD_LIBRARY_PATH=$HOME/lib:$HOME/lib64:$LD_LIBRARY_PATH

set -o vi

