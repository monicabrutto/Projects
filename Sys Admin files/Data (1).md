### Monica Brutto, CEG 2410


# Part 1 - Server Configuration
### Choice of RAID configuration & justification
* RAID 5
* I choose RAID 5 because data is striped with parity across drives which means it allows you have one disk fail and you are to rebuild lost data from partiy shored on the other drives. RAID 5 also has fast read ablilties which is perfect for the business I choose (Museum) in which research is the focous. It does have slower write speed but it is worth it to have the parity. The minimum number of disk is 3, but it can do up to 16 allowing for good scalability. RAID 5 has better redundancy with more usable capacity.
### How to configure, mount, and automatically mount RAID
  1. In AWS, go to EC2 instnaces, find volumes and create three new volumes.
  2. On the terminal, use `lsblk` to find the lisk of blocks on the instnace. Then run `sudo fdisk /dev/name` on each new volume created.
            * This will create a partition on the disk. Use `n` and `w` to create the default partitions.
  3. Next, use mdadm to create the RAID using the disks.
     * `sudo mdadm --create --verbose /dev/md/5 --level=5 --name=MY_RAID --raid-devices=3 /dev/xvdg /dev/xvdh /dev/xvdi`
       * --create means create the raid
       * --verbose means to show extra outputs and warnings
       * /dev/md/5 is the name of the RAID - I choose to do 5 since the RAID is a RAID5 but this should be a better name. Shows up as md5
       * --level=5 indicates the level of RAID, so if you are going to do a level 6 then the flag should be --level=6
       * --name=MY_RAID is just a name flag, can be anything
       * --raid-devices=3 indicates the number of disks you want to use and then expects that number to be listed.
       * list the disks you want to use.
  4. To add a file system, use the mkfs command and the name of the RAID in this case md5
     * `sudo mkfs.ext4 /dev/md5`
     *  Using the ext4 files sytem.
  5. Next, to mount to the system, make a directoy in /mnt folder on root and them using the mount command, mount md5
     * `sudo mkdir /mnt/raid`
            * I called this directoy raid because its used for the RAID.
     * `sudo mount /dev/md5 /mnt/raid`
            * must use the path /dev/md5 or whatever name given here to mount and then the path of the directory.
     * Note when the instance is booted but the RAID is not mounted it changes the name to md127.
6. Lastly set up automatic mounting by creating new rule in fstab
   * `sudo mdadm --detail --scan | sudo tee -a /etc/mdadm/mdadm.conf`
   * `sudo update-initramfs -u`
       * so that the array will be available during the early boot process
   *  `echo '/dev/md5 /mnt/raid ext4 defaults,nofail,discard 0 0' | sudo tee -a /etc/fstab`
       * This command adds the new filesystem mount options to the /etc/fstab file for automatic mounting at boot
### Method to recover RAID in case of failure
 * In the event of disk failure, data can be recovered.
 * A good starting place is to back up the current back to another storage type that way if the recovery process fails then there still is the data.
 * `mdadm --misc --detail /dev/md5` this command shows the details of the RAID andd can be uesd to determine the state of the disks.
 * Similarly, using `# fdisk -l /dev/name` can be used to examine the failed disk.
 * Then you can copy the partion table from a working drive to replace the failed one.
 * Next, reconstruct the partition table on the new drive to start the rebuidling of the array.
 * There are other tools and software out there that can help reconstruct the RAID but they wouldn't necessarily work with AWS.
 * [How to recover linux RAID using mdadm](https://recoverit.wondershare.com/harddrive-recovery/linux-raid-recovery.html)
### Screenshot with RAID status & proof of mount
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/995202a5-8e16-4d76-8915-0460aa19f8ab)
---------------------------------------------------------------------------------------------------------------------------------
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/58fcaf96-0fca-43d5-8bf2-d6030bff0a1d)


# Part 2 - Service Configuration
## Justification for choosing SAMBA or NFS along with 2 key points that made it a choice advantage for you. Reasons such as "it sounded nice" will get no credit.
* SAMBA
* Is an open source version of SMB which has a widely adopted protocol that is supported by a variety of operating systems, including Windows, macOS, Linux, and Android
* SMB supports file locking, which ensures that files are not changed by multiple users simultaneously, which will minimize the risk of data loss or corruption
## How to configure
* I created another VPC to test this out but that is not really necessary, I just didn't want to mess up anything on my personal system
* Need to Create another VPC
   * New Route table 
   * New internet gateway
   * New security group
   * New Instance
   * New Elastic IP
* Install SAMBA
  * Run `sudo apt update` first then run `sudo apt install samba` to install
* Create a shared Directory on the host
    * `sudo mkdir /mnt/raid/share`
    * Use the directory that holds the raid
* Configure SAMBA file
    * `sudo vim /etc/samba/smb.conf`
    * Add the following to the end of the file
     ```
      [share]
      comment = Samba on Ubuntu path = /mnt/raid/share
      read only = no
      browsable = yes
     ```
    * read only: Permission to modify the contents of the share folder is only granted when the value of this directive is no.
    * browsable: When set to yes, file managers such as Ubuntu’s default file manager will list this share under “Network”.
* Save and Restart to ensure the rules are in place
  * `sudo service smbd restart`
* Upate the firewall to allow SAMBA users in
   * `sudo ufw allow samba`
   * Also allow ssh to make sure you can connect to the instance
* Set users to be able to connect to SAMBA
   * `sudo smbpasswd -a username` with username being the name of the user so I did unbuntu. Which will create a new SMB password
   * then create a new password, I put the password as Iliketoshare to I would remember it and I am writting it here for future reference.
* On the client or another instance in this case.
  * `sudo apt install smbclient` to install the client side of SMB, make sure to update first
  *  `smbclient //44.221.152.0/share -U ubuntu` with ip of the host (where the raid is) and the file name with the username from up above.
  *  Once typing in the passowrd you should see the `smb:\>` prompt
## Screenshot with proof of setup
  ![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/71262f23-2298-4672-a403-d15c5a48f81d)
  ---------------------------------------------------------------------------------------------------------------------------
  ![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/02a922f9-023e-49c2-a76f-0530f1b7c30a)
  ---------------------------------------------------------------------------------------------------------------------------
  ![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/d0fec1fe-f0cb-490f-b1d4-f635fd833b37)

  
# Part 3 - Server Network Security
## List the trusted subnets
* 130.108.0.0/16 (WSU) 
* 34.194.224.138/32 (other VPC)
## List the required ports (and note protocols if specified)
* Port 22 (SSH)
* Port 11 (TCP)
* Port 139 (TCP)
* Port 445 (TCP) 
* Port 2049 (TCP) 
## Screenshot your Security Group rules
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/ed8f1e80-7437-43d2-97ce-cb5f66410609)


# Part 4 - Data Compliance
## Identify what compliance guidelines your organization will need to be concerned with
* Since most museums are government funded, my organization will need to concerned with NIST complaince.
* Nine Keypoints:
1. Categorize the data and information you need to protect
2. Develop a baseline for the minimum controls required to protect that information
3. Conduct risk assessments to refine your baseline controls>
4. Document your baseline controls in a written security plan
5. Roll out security controls to your information systems
6. Once implemented, monitor performance to measure the efficacy of security controls
7. Determine agency-level risk based on your assessment of security controls
8. Authorize the information system for processing
9. Continuously monitor your security controls

## Identify how you will restrict access to the data while giving access to those who need it
* Using SAMBA, you can set certian directories and files for certian groups. For example, if you can create a user in the file share that only has access to one file.
* Using security groups, you can restrict access to the file share as whole. By only allowing certian subnets, say IT Admin, access the TCP ports for the file share then we can restirct those who should have access, but those with the correct IP subnet can access. 
## Identify what happens if a compliance violation occurs
* If a compliance violation occurs, users should be notifed if the violation included the leak of information.
* The violation should be documented and then fixed. (report and remedy) 
* Violating NIST complaince could end with be fines or crimminal/civil charges.
* Other ramifcations incldue loss of clients and loss of reputation, loss of productivity. 


