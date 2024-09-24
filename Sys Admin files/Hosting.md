## Part 1 - HTTP Server
### Apache Install
* `sudo apt update`
* `sudo apt install apache2`
  * By defualt upon install apache is running on port 80
  * Default is http because it needs certifcations for https
* Tests to see if it is running
    * `sudo systemctl status apache2`
    * `curl localhost:80`
    * `curl 10.0.0.13` which is the private ip of the instance
    * `curl 44.221.152.0` which is the public ip of the instance
          * Need to chnage security groups if this comes up as nothing.
          * Which it does, so need to add port to allow inbound traffic from public ip in this case mine is 44.221.152.0
### Default port & site directory
* The default port is 80
* Need to allow port 80 traffic from the instance and wsu ip.
* Enter ip into a web browser and you can see the website running.
* Don't want to use apache's index.html
   * instead use: `sudo mkdir /var/www/monicasite`
   * This makes a new direcotry in the www directory, in here is where we put our html and css files.
   * make a file inside the new directory called index.html
* Next, to change to the this site running instead of the default you have to create a sites-avaliable conf file
   * `sudo vim /etc/apache2/sites-available/monicasite.conf`
~~~
        <VirtualHost *:80>
        ServerAdmin webmaster@localhost
        ServerName monicasite
        ServerAlias www.monicasite
        DocumentRoot /var/www/monicasite
        ErrorLog ${APACHE_LOG_DIR}/error.log
        CustomLog ${APACHE_LOG_DIR}/access.log combined
        </VirtualHost>
~~~
* This changes `DocumentRoot` to the new monicasite directory and added ServerName, which establishes the base domain and ServerAlias, which defines aliases based on the new direcory name. Alternatively, you could change the conf file to have the new directory in it. (Domain and ServerAlias will come in handy later but right now, it could be left on default) 
* `sudo a2ensite monicasite.conf` enables the new site
* `sudo a2dissite 000-default.conf` which disables the old site.
* `sudo apache2ctl configtest` checks for config errors
* then, once it shows up as syntax ok, `sudo systemctl reload apache2` to relaod apache.
* Two ways to check it's working
  * curl 44.221.152.0
      * output should be the new index.html file not the apache2
  * refresh browser and check that the new index file is displayed

### Site administration
* Conf files
   * /etc/apache2/sites-available
     * default-ssl.conf
               * configures http and Certificates
               * location matters because these are in the available direcotry meaning they are not site enabled. Available are sites conf ready to be deployed or 
                  being worked on and are not yet up and enabled. 
           * 000-default.conf
               * Configures appaches default website, port 80 or http 
               * has path to website, serverName, error logs
   * In /etc/apache2/sites-enabled there is enabled sites, since I created a new conf for my site instead of editing the default, monicasite.conf is in this 
     direcotry and is enabled which means the site is running.  
* Configuration of permissions for website files
     * first we make a new group using `sudo groupadd devs`
     * Then we can set the permissions of the directory to add the group devs on it using `sudo chmod 775 monicasite/`
       * Gives r+wx to user and group and r+x to other
     * Next change the group for the directory using ` sudo chgrp -R devs monicasite/`
          * -R means it will change the group for all files and folders inside this directory
     * Finally, to make sure that every time a new file/folder is created the group has access, set the setgid or set group id.
          * `sudo chmod g+s monicasite/`
          * g stands for group, s stands for set id
### Screenshots
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/d17c6cf8-a87e-4e69-924f-f3c3a0ea0849)

![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/32919e45-028f-4fd4-b8b1-fbbd5cb40456)

------------------------------------------------------------------------------------------------------------------------------
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/f35b866f-a670-4913-bfd5-faf5c547506f)

-----------------------------------------------------------------------------------------------
[I used this resource for apache setup](https://www.digitalocean.com/community/tutorials/how-to-install-the-apache-web-server-on-ubuntu-20-04)

[I used this resource for setgid](https://www.liquidweb.com/kb/how-do-i-set-up-setuid-setgid-and-sticky-bits-on-linux/)


## Part 2 - Enable HTTPS
### Creating & location of self-signed certificate files
* `sudo a2enmod ssl`
* `sudo systemctl restart apache2`
* `sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/apache-selfsigned.key -out /etc/ssl/certs/apache-selfsigned.crt`
  * openssl a command line tool for creating certs, keys and other files
  * req specifies to use X.509 certificate signing request management
  * x509 modifies req to tell it that this will be self-signed instead of creating a signing request.
  * nodes skips the option to secure the cert with a passphrase
  * days 365 sets the length that the cert will be valid
  * newkey rsa:2048 specifics that the cert and key are both new and that the key is 2048 bits long.
  * keyout specifis the location for the key and out specifis the location for the cert. 
* Enter information for the website including country, state, email address, common name, etc. The most important one is the Common Name as this needs to be the hostname that will be used.
* The certifcate is loacted in the `/etc/ssl/certs` directory and I named it `apache-selfsigned.crt`
* The cert key is located in the `/etc/ssl/private` direcotry and I named it `apache-selfsigned.key` 
### Service configuration file changes & description of reason / why
  * Created following 443 conf file to enable https and assgin the ssl certficate to the website 
  ~~~
  <VirtualHost *:443>
   ServerName monicasite
   DocumentRoot /var/www/monicasite

   SSLEngine on
   SSLCertificateFile /etc/ssl/certs/apache-selfsigned.crt
   SSLCertificateKeyFile /etc/ssl/private/apache-selfsigned.key
  </VirtualHost>
   ~~~
* For redirect in a seperate file, I created a 80 conf that has a redirection instruction.
  ~~~
  <VirtualHost *:80>
    ServerAdmin webmaster@localhost
    ServerName monicasite.com
    Redirect / https://44.221.152.0
    DocumentRoot /var/www/monicasite
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
  </VirtualHost>
  ~~~
### Service administrative commands 
* `sudo a2ensite monicasite.conf` to enable the conf file
     * Might also have to disable other conf files: `sudo a2dissite default.conf` 
* `sudo systemctl reload apache2` to restart the web service and use the newly enabled conf file. 
* How you can confirm HTTPS is enabled
  * `sudo nmap -n 44.221.152.01` run nmap to see that port 443 is open for all inbound traffice
  * `curl 44.221.152.0` will show that the site has moved to https
  ~~~
          <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
          <html><head>
          <title>302 Found</title>
          </head><body>
          <h1>Found</h1>
          <p>The document has moved <a href="https://44.221.152.0">here</a>.</p>
          <hr>
          <address>Apache/2.4.52 (Ubuntu) Server at 44.221.152.0 Port 80</address>
          </body></html>
  ~~~
  * Got to browser and type in https://44.221.152.0 (may neeed to hit advance). Then you can see the site is up and running
  * With http forwarding to https, you can also just type the ip address in and it will take you to the site. 
### Screenshot of site after HTTPS is enabled
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/73318194-ecdd-455d-9fd0-ee910849703c)

![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/1b49b21d-5aaf-451e-9b1e-1c2787a5129a)


----------------------------------------------------------------------------------------------------------------
[I used this link for part 2](https://www.digitalocean.com/community/tutorials/how-to-create-a-self-signed-ssl-certificate-for-apache-in-ubuntu-16-04#step-3-configure-apache-to-use-ssl)

## Part 3 - Firewall Fixes
### Explain updates to Security Group in terms of protocols, ports, and sources
* SSH - port 22, it is needed to sign on to the instance, since I live on campus I just needed to make sure inbound was allowed for the subnet 130.108.0.0/16
* HTTP - port 80, to allow from any soucre the subnet will be 0.0.0.0/0 meaning all bits can be changed
* HTTPs - port 443, to allow from any soucre the subnet will be 0.0.0.0/0 meaning all bits can be changed
### Screenshot
 ![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/a47c42d4-ac0a-4492-ab99-2e280924b780)


## Part 4 - DNS
### Choose a domain name for your website.  
* I choose `monicasite.com` and looked up in ICANN to see if it was taken and it is not. 
### Write an A record
~~~
www.monicasite.com IN A 44.221.152.0
~~~
* <host> in this case is my domain `www.monicasite.com`
* IN means it points to an IP address and in this case A means an IPv4 address and the address is 44.221.152.0
* The purpose of the A record is to create a map the domian to an IP address. 
### Write a CNAME record
~~~
monicasite.com IN CNAME www.monicasite.com
~~~
* The first part is the Alias to the website which can then be typed in to the browser and it will still go to www.monicasite.com like searching google.com instead of www.google.com
* IN CNAME specifics that we are pointing to / redirecting to the the full domain address
* The purpose of CNAME is to allow alias to be used for the website and to map subdomains to the host domain. 

---------------------------------------------------------------------
[I used this link for A records research](https://www.cloudflare.com/learning/dns/dns-records/dns-a-record/)

[I used this link for CNAME records research](https://www.cloudflare.com/learning/dns/dns-records/dns-cname-record/)


## Part 5 - Research
### Domain name registration
* I choose to use Cloudflare Registrar
     * Then search for a domain on their website and they will tell you what is available and what is not
     * Then you purchase the right to that domain.
     * Once you have the domain, you would need to update the conf files to include serverName as the new domain and then change to DNS records to include the new 
domain name and aliases. 
### Certificate Authority Validation
* Cloudflare SSL/TLS Certifcates
* For the basic one domain certficate, all you need to do is prove that you own/contorl the domain. Often validation is done through the email but if you use the same compnay for CA and Domain Registrar proving you own the domain would be easy. 
* For the next level up, an organization ssl you would need a business name and address.
---------------------------------------------------------------------------------
[I used this link for Domina name info](https://www.cloudflare.com/learning/dns/glossary/what-is-a-domain-name-registrar/) 

[I used this link for CA info](https://www.cloudflare.com/learning/ssl/types-of-ssl-certificates/) 



