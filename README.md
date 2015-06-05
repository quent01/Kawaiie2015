# Kawaiie 2015
==========

## Installation
- install vagrant on your machine
- clone the repository
- install drupal core in public/
- ...



## Vagrant

### Useful Stuff
- PHP 5.5
- No Internet connection required
- PHP errors turned on
- Laravel and WordPress ready (and others)
- Operating System agnostic
- Goodbye XAMPP / WAMP
- New Vagrant version? Update worry free. ScotchBox is very reliable with a lesser chance of breaking with various updates
- Bootstrap and jQuery are saved in the server's home folder in case you don't have Internet (usually planes, trains or cars)
- Chef and Puppet ready in case you want to add extra features on Vagrant Up
- Super easy database access and control
    MIT License

### Server Stuff
- Apache
- Vim
- MySQL
- PHP 5.5
- Git
- Screen
- Composer
- cURL
- GD and Imagick
- Mcrypt
- Memcache and Memcached

### Front End Stuff
- NPM
- Grunt
- Bower
- Yeoman
- Gulp


## Get Started

* Download and Install Vagrant
* Download and Install VirtualBox
* Clone the Repository
* **Install Drupal Core** in public/
* Run Vagrant Up
* Access Your Project at  [http://192.168.33.10/](http://192.168.33.10/)


## Basic Vagrant Commands

### Start or resume your server
```bash
vagrant up
```

### Pause your server
```bash
vagrant suspend
```

### Delete your server
```bash
vagrant destroy
```

### SSH into your server
```bash
vagrant ssh
```


## Database Access

| Key  | Value |
| ------------- | ------------- |
| Database Name  | scotchbox  |
| Database User  | root  |
| Database Password  | root  |
| Database Host  | localhost / 127.0.0.1  |
| SSH Host  | 192.168.33.10  |
| SSH User  | vagrant  |
| SSH Password  | vagrant  |




## Updating the Box

Although not necessary, if you want to check for updates, just type:

```bash
vagrant box outdated
```

It will tell you if you are running the latest version or not of the box. If it says you aren't, simply run:

```bash
vagrant box update
```


## Setting a Hostname

If you're like me, you prefer to develop at a domain name versus an IP address. If you want to get rid of the some-what ugly IP address, just add a record like the following example to your laptop's host file.

```bash
192.168.33.10 local.dev
```
