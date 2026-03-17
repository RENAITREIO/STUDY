# The Missing Semester of Your CS Education
## Shell
Bourne Again SHell(bash)

command:  
`date` `echo` `which` `pwd` `cd` `ls` `mv` `cp` `mkdir` `man` `cat` `tac` `find` `tee` `sudo`

redirection operator: `<` `>` `>>`  
pipe operator: `|`

environment `$PATH`

## Shell Tolls and Scripting
function
```sh
mcd () {
    mkdir -p "$1"
    cd "$1"
}
```
- `$0` - Name of the script
- `$1` to `$9` - Arguments to the script. `$1` is the first argument and so on.
- `$@` - All the arguments
- `$#` - Number of arguments
- `$?` - Return code of the previous command
- `$$` - Process identification number (PID) for the current script
- `!!` - Entire last command, including arguments. A common pattern is to execute a command only for it to fail due to missing permissions; you can quickly re-execute the command with `sudo` by doing `sudo !!`
- `$_` - Last argument from the last command. If you are in an interactive shell, you can also quickly get this value by typing `Esc` followed by `.` or `Alt+.`

short-circuiting

`$( CMD )` command substitution  
`<( CMD )` process substitution

globbing  
- wildcards: `?` and `*`
- curly braces: `{}`

shebang  
`env` command such as `#!/usr/bin/env python`

export

`tldr`(TLDR pages)

`find . -name [name] -type [type]`  
`fd`  
`locate`

`grep`  
`ack`  
`ag`  
`rg`

`history`  
`Ctrl+R`  
`fzf`  

`fasd`  
`autojump`  
`tree`  
`broot`

## Vim
Mode
- Normal: for moving around a file and making edits
- Insert: for inserting text
- Replace: for replacing text
- Visual (plain, line, or block): for selecting blocks of text
- Command-line: for running a command

command-line
- `:q` quit (close window)
- `:w` save (“write”)
- `:wq` save and quit
- `:e {name of file}` open file for editing
- `:ls` show open buffers
- `:help {topic}` open help
  - `:help :w` opens help for the :w command
  - `:help w` opens help for the w movement

movement
- Basic movement: `hjkl` (left, down, up, right)
- Words: `w` (next word), `b` (beginning of word), `e` (end of word)
- Lines: `0` (beginning of line), `^` (first non-blank character), `$` (end of line)
- Screen: `H` (top of screen), `M` (middle of screen), `L` (bottom of screen)
- Scroll: `Ctrl-u` (up), `Ctrl-d` (down)
- File: `gg` (beginning of file), `G` (end of file)
- Line numbers: `:{number}<CR>` or `{number}G` (line {number})
- Misc: `%` (corresponding item)
- Find: `f{character}`, `t{character}`, `F{character}`, `T{character}`
  - find/to forward/backward {character} on the current line
  - `,` / `;` for navigating matches
- Search: `/{regex}`, `n` / `N` for navigating matches

selection
- Visual: `v`
- Visual Line: `V`
- Visual Block: `Ctrl-v`

edits
- `i` enter Insert mode
  - but for manipulating/deleting text, want to use something more than backspace
- `o` / `O` insert line below / above
- `d{motion}` delete {motion}
  - e.g. `dw` is delete word, `d$` is delete to end of line, `d0` is delete to beginning of line
- `c{motion}` change {motion}
  - e.g. `cw` is change word
  - like `d{motion}` followed by `i`
- `x` delete character (equal to `dl`)
- `s` substitute character (equal to `cl`)
- Visual mode + manipulation
  - select text, `d` to delete it or `c` to change it
- `u` to undo, `<C-r>` to redo
- `y` to copy / “yank” (some other commands like `d` also copy)
- `p` to paste
- Lots more to learn: e.g. `~` flips the case of a character
- `.` repeat operation

counts
- `3w` move 3 words forward
- `5j` move 5 lines down
- `7dw` delete 7 words

modifiers
- `ci(` change the contents inside the current pair of parentheses
- `ci[` change the contents inside the current pair of square brackets
- `da'` delete a single-quoted string, including the surrounding single quotes

## Data Wranglin
`ssh`

`sed` + `s/REGEX/SUBSTITUTION/`

regular expressions
- `.` means “any single character” except newline
- `*` zero or more of the preceding match
- `+` one or more of the preceding match
- `[abc]` any one character of `a`, `b`, and `c`
- `(RX1|RX2)` either something that matches `RX1` or `RX2`
- `^` the start of the line
- `$` the end of the line
- `\d` any digit
- `\w` any alphanumeric character
- `\s` any whitespace
- `{m}` m repetitions
- `{m,n}` m to n repetitions
- `(...)` capture group

suffix * or + with a ? to make them non-greedy

`sort` `uniq -c` `head` `tail` `paste`

`awk`

do not substitude the same file with `>`, because the shell will clear the file after `>` in the first

## job control
`Ctrl-C` `SIGINT`
`Ctrl-\` `SIGQUIT`
`Ctrl-Z` `SIGSTOP`

`Ctrl-D` `EOF`

`nohup`

tmux  
~~*but i use kitty*~~

## aliases
`alias alias_name="command_to_alias arg1 arg2"`

`ssh foobar@server command` 

`ssh-keygen` `ssh-agent`

copying files over SSH `ssh + tee` `scp` `rsync`

port forwarding

## git
```
// a file is a bunch of bytes
type blob = array<byte>

// a directory contains named files and directories
type tree = map<string, tree | blob>

// a commit has parents, metadata, and the top-level tree
type commit = struct {
    parents: array<commit>
    author: string
    message: string
    snapshot: tree
}

type object = blob | tree | commit

objects = map<string, object>

def store(object):
    id = sha1(object)
    objects[id] = object

def load(id):
    return objects[id]

references = map<string, string>

def update_reference(name, id):
    references[name] = id

def read_reference(name):
    return references[name]

def load_reference(name_or_id):
    if name_or_id in references:
        return load(references[name_or_id])
    else:
        return load(name_or_id)
```

commands
```
git cat-file -p

git help <command>
git init
git status
git add <filename>
git commit
git log [--all --graph --decorate --oneline]
git diff <filename>
git checkout <revision>

git branch
git branch <name>
git checkout -b <name>
git merge <revision>
git mergetool
git rebase

git remote
git remote add <name> <url>
git push <remote> <local branch>:<remote branch>
git branch --set-upstream-to=<remote>/<remote branch>
git fetch
git pull
git clone

git commit --amend
git reset HEAD <file>
git checkout -- <file>

git config
git clone --depth=1
git add -p
git rebase -i
git blame
git stash
git bisect
```

.gitignore

## debugging and profiling
debugging
- printf
- logging  
  `logger` `lnav`
- debuggers  
  for python: `pdb` `ipdb`  
  for c: `gdb` `pwndbg` `lldb`
- specialized tools  
  system calls: `strace`  
  network packets: `tcpdump` and wireshark  
  web development: Chrome/Firefox developer tools
- static analysis  
  for python: `pyflakes` `mypy`  
  for shell: `shellcheck`  

profiling
- **timing**  
  `time` real, user, sys
- **profilers**
  - *CPU*  
    for python: `cProfile` `line-profiler`
  - *event profiling*  
    `perf`
  - *visualization*  
    flame graph  
    for python: `pycallgraph`
  - *resource monitoring*
    - general monitoring  
      `htop` `dool`
    - I/O operations  
      `iotop`
    - disk usage  
      `df` `du` `ncdu`
    - memory usage  
      `free` `htop`
    - open files  
      `lsof`
    - network connecions and config  
      `ss` `ip`
    - network usage  
      `nethogs` `iftop`
  - *specialized tools*  
    `hyperfine`

## metaprogramming
bulid systems  
`make`
```makefile
paper.pdf: paper.tex plot-data.png
	pdflatex paper.tex

plot-%.png: %.dat plot.py
	./plot.py -i $*.dat -o $@
```

dependency management  
repository  
versioning
- **time**
- **semantic versioning**
  - If a new release does not change the API, increase the patch version.
  - If you add to your API in a backwards-compatible way, increase the minor version.
  - If you change the API in a non-backwards-compatible way, increase the major version.

lock files

**continuous integration(CI) systems**: an umbrella term for “stuff that runs whenever your code changes”

testing
- **Test suite**: a collective term for all the tests
- **Unit test**: a “micro-test” that tests a specific feature in isolation
- **Integration test**: a “macro-test” that runs a larger part of the system to check that different feature or components work together.
- **Regression test**: a test that implements a particular pattern that previously caused a bug to ensure that the bug does not resurface.
- **Mocking**: to replace a function, module, or type with a fake implementation to avoid testing unrelated functionality. For example, you might “mock the network” or “mock the disk”.

## security and cryptography
entropy: a measure of randomness

### hash functions  
properties
- **Deterministic**: the same input always generates the same output.
- **Non-invertible**: it is hard to find an input m such that hash(m) = h for some desired output h.
- **Target collision resistant**: given an input m_1, it’s hard to find a different input m_2 such that hash(m_1) = hash(m_2).
- **Collision resistant**: it’s hard to find two inputs m_1 and m_2 such that hash(m_1) = hash(m_2) (note that this is a strictly stronger property than target collision resistance).

SHA1: 160-bit outputs, but not safe
  ```sh
  printf 'msg' | sha1sum
  ```

applications
- git, for content-addressed storage
- a short summary of the contents of a file
- commitment schemes

### key derivation functions(KDF): slow
- Producing keys from passphrases for use in other cryptographic algorithms
- Storing login credentials  
  generate and store a random salt `salt = random()`  
  store `KDF(password + salt)`

### symmetric cryptography
```
keygen() -> key  (this function is randomized)

encrypt(plaintext: array<byte>, key) -> array<byte>  (the ciphertext)
decrypt(ciphertext: array<byte>, key) -> array<byte>  (the plaintext)
```
`decrypt(encrypt(m, k), k) = m`  
Encrypting files for storage in an untrusted cloud service. This can be combined with KDFs, so you can encrypt a file with a passphrase. Generate `key = KDF(passphrase)`, and then store `encrypt(file, key)`.

### asymmetric cryptography
```
keygen() -> (public key, private key)  (this function is randomized)

encrypt(plaintext: array<byte>, public key) -> array<byte>  (the ciphertext)
decrypt(ciphertext: array<byte>, private key) -> array<byte>  (the plaintext)

sign(message: array<byte>, private key) -> array<byte>  (the signature)
verify(message: array<byte>, signature: array<byte>, public key) -> bool  (whether or not the signature is valid)
```
`decrypt(encrypt(m, public key), private key) = m`  
`verify(message, sign(message, private key), public key) = true`

application
- PGP email encryption.
- Private messaging.
- Signing software.

password managers  
two-factor authentication  
full disk encryption  
SSH

## others
**keyboard remapping**: you can map keys to other keys or commands

**daemons**: a series of processes that are running in the background  
`sshd` `systemd` `cron`

**FUSE**: filesystem in user space  
- *sshfs* - Open locally remote files/folder through an SSH connection.
- *rclone* - Mount cloud storage services like Dropbox, GDrive, Amazon S3 or Google Cloud Storage and open data locally.
- *gocryptfs* - Encrypted overlay system. Files are stored encrypted but once the FS is mounted they appear as plaintext in the mountpoint.
- *kbfs* - Distributed filesystem with end-to-end encryption. You can have private, shared and public folders.
- *borgbackup* - Mount your deduplicated, compressed and encrypted backups for ease of browsing.

backups

APIs

Common command-line flags/patterns
- `--verbose` or `-v` flag to produce more verbose output
- `-` in place of a file name means “standard input” or “standard output”, depending on the argument.
- `--` pass something that looks like a flag as a normal argument(`rm -- -r`)

window managers

VPNs

markdown

booting + live USBs

docker, vagrant, VMs, cloud, openstack

notebook programming: such as jupyter book
