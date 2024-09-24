# Project 3 - Identity Management with Active Directory
## Setup AD DC
### Prep
  * Use Sever Manager software to install features
      * Select DNS and AD Domain sevices
  * Can rename system to be more specifc and easier to use, I renamed to DC1
### Set up Domain Controller
* In Server Manager there should be a flag raised in the top right corner, click on it, and click on promote this to a domain controller.
* Select Add a new forest, and create a new Root domain name. I set mine to `monica.com`
* Choose which functional level, left ours on Windows Server 2016
* Select the DNS server and Global Catlog checkboxes
* Create a password for the DSRM
* Skip the next section, not setting up a specifc DNS config right now.
* For additional options menu, you can keep the default netBIOS domain name.
* Next is Paths for the loaction of the AD DS database, log files, and SYSVOL. Choose default
* After reviewing opiton schoosen, run pre-req check. If the check comesback good, then click install which will restart the system.

### Powershell Script
```
#
# Windows PowerShell script for AD DS Deployment
#

Import-Module ADDSDeployment
Install-ADDSForest `
-CreateDnsDelegation:$false `
-DatabasePath "C:\Windows\NTDS" `
-DomainMode "WinThreshold" `
-DomainName "monica.com" `
-DomainNetbiosName "MONICA" `
-ForestMode "WinThreshold" `
-InstallDns:$true `
-LogPath "C:\Windows\NTDS" `
-NoRebootOnCompletion:$false `
-SysvolPath "C:\Windows\SYSVOL" `
-Force:$true
```
- Domain Name: monica.com
- Domain Controller Name: DC1
- Domain DNS IP: 127.0.0.1

## AD Structure
### Create OUs
Create the following Organizational Units - Provide screenshot proof:

- `[Domain] Computers` - client / user machines
  - `Conference` - publicly accessible kiosks and presentation devices
  - `Secure` - machines for HR and finance users
  - `Workstations` - machines for developers and engineers
- `[Domain] Servers` - servers for org (data shares, repo hosts, HPCs)
- `[Domain] Users`
  - `Finance` - can log on to Secure computers, managed by hr_finance_admins group
  - `HR` - can log on to Secure computers, managed by hr_finance_admins group
  - `Engineers` - can log on to Workstations, managed by dev_eng_admins
  - `Developers` - can log on to Workstations, managed by dev_eng_admins
 
  ![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/1c548ef0-1a83-460d-8f04-428e5604daae)
  
### Joining Users
#### Screenshot that users are in correct OUs
 ![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/70147a28-1e0d-4204-a0f2-2178fcd518e0)

### Joining Computers

#### Write the steps needed to join the Windows Server to the Domain in the `[Domain] Computers` OU. 
* Created a new windows server in AWS. Signed into it, changed name to `comp1`
* Make sure to change security groups to include inbound all traffic from the intances
  
---------------------------------------------------------------------------------------------------------------
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/e1460cd6-4987-485c-9694-8e38bb569e36)
---------------------------------------------------------------------------------------------------------------

* Open System Properties on comp1 by running the `sysdm.cpl`
   * Click on `change` next to change name or domain in order to change the domain of this computer
* Change the domain name to be the domain name of our domain controller which is `monica.com`. This prompts the user to enter login information and then restart the computer. 
   * If that does work, go to ethernet settings and select `Network and Sharing center` and then ethernet to get ethernet status.
   * Select properties, double click on IPv4 connection and select `"Use the following DNS server addresses`.
   * Enter DNS information with AD's private IP address in my case `10.0.0.11` and the DNS IP `10.0.0.2`
   * Next go back one menu and select Advanced settings, Added a DNS suffix to my domain `monica.com`


#### Provide screenshot proof of success.
* I couldn't capture before the restart, but I was able to confrim that it is apart of the domain by searching in settings see second screenshot. 

![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/7ac6dd7a-552f-4ca4-9e2d-a07beb2a6a34)
![image](https://github.com/WSU-kduncan/ceg2410s24-monicabrutto/assets/111888056/f36a2dfd-7dbd-4597-ab36-9870f030dfb9)

**Resources:**
  - https://adamtheautomator.com/add-computer-to-domain/

### Creating Groups

Create the following Security Groups and define where they should be within the OUs based on their roles:

* `project_repos_RW` - users who have Read / Write access to project repositories
    * Should be a group of Developers that work on the projects, could be individualized. Domain local
 * `finance_RW` - users who have Read / Write access to finance share
    * Finance employees that neeed acess to certain files/folders, goes under finace users. Domain local
* `onboarding_R` - users who have Read access to onboarding documents
   * HR handles all onboarding materials, so under the HR users. However, it could depend on the materials, say finance needs a document for training and it is in the onboaridng. But in this case, I went with
     just HR because materials is a broad term. Domain local
* `server_access` - users who can log on to Servers
  * Only developers and IT admins should have access. Global
* `dev_eng_admins` - IT admins to handle Developer and Engineer accounts Domain Local
  * Since this group handles both Deves and Engieers this should go with both groups. 
* `hr_finance_admins` - IT admins to handle HR and finance accounts. Domain Lcoal
  * Since this group handles both HR and Finance this should go with both groups. Domain Local
* `remote_workstation` - Group of workstations that allow RDP connections
  * Appiled to the workstations OU not users, allows RDP connection to only those computers. Domain local


## OUs & GPOs

### Applying Group Policies

Find guides to create the following Group Policy Objects and specify where they should be applied.

* [Lock out Workstations after 15 minutes of inactivity.](https://www.encyro.com/blog/how-to-force-windows-10-to-lock-itself-after-inactivity-for-all-users#:~:text=Setting%202%3A%20Screen%20Saver%20Timeout&text=Select%20%E2%80%9CEnabled%E2%80%9D%20and%20set%20the,Click%20OK.)
   * This should be applied to computers that hold sensative information so our secure group for finacne, HR, and the workstations for developers. Computers in the conference OU shouldn't lock because they would be used to present information and could be running for longer times. 
* [Prevent execution of programs on computers in Secure OU](https://learn.microsoft.com/en-us/windows-server/identity/software-restriction-policies/software-restriction-policies)
  * This should be applied to any computer where untrusted users may use them or where users don't need to be downlaoding software. For example, HR and finance does not need VS code and the packages that come with that, but developers may need to. However, developers don't need acess to HR's software. 
* [Disable Guest account login to computers in Secure OU](https://www.isumsoft.com/windows-10/enable-disable-guest-account-in-windows-10.html)
  * This should be applied to all computers execpt Conference because only emplyoees should have access to the computers and the snestive data that comes with it. 
* [Allow server_access to sign on to Servers](https://learn.microsoft.com/en-us/system-center/scsm/enable-service-log-on-sm?view=sc-sm-2022)
  * This should be applied to our servers OU because no other OU or group should have to access the servers. 
* [Set Desktop background for Conference computers to company logo.](https://www.serveracademy.com/courses/group-policy-security-with-windows-server/deploying-a-desktop-background-to-your-domain-with-gpo-group-policy-object/#:~:text=Under%20User%20Configuration%20navigate%20to,Wallpaper%20to%20edit%20the%20setting.)
   * This should be set for our Conference OU so all backgrounds are the same. 
* [Allow users in `remote_workstation` group to RDP to Workstations](https://www.prajwaldesai.com/enable-remote-desktop-using-group-policy-gpo/)
   * This should be applied to the remote_workstations group, to allow remote desktop. Workstations are for the developers and Engineers

### Managing OUs
#### Join at least one person to the `hr_finance_admins` and `eng_dev_admins` groups, respectively. Delegate control of the OUs corresponding to the appropriate admin groups.
Document how to delegate control of an OU to a group, which OUs they now delegate, and what permissions they were given (and why you think the scope is appropriate)
* Promoted Jessy Jones to hr_finance_admins by changing the members of the group under the scope
* Then went to Users and Computers clicked on the right clicked on the finance OU and hit delegated control
* There should a Wizzard that pops up and then you can add what you want them to have permission over. 
  * I game this user permission to Create, delete, and manage user accounts, reset user passowrds, create, delete, and manage groups, modfiy memebership of this group, and manage GPOs.
  * I choose this scope because as an admin this person is suppose to be able to delegate accounts to new memebers, chaage passowrds, and overall manage the user accounts. Since the groups are Domain local, they won't be able to access all account in the domain, which insures they are acting within their scope. 
* Next, I promoted Izzie Ochoa from the developers OU to the eng_devs_admin group. I did this by again going to the group in the OU, right clicked and added the user to as a member of the group
   * I gave her permission to  Create, delete, and manage user accounts, Reset user passwords and force password change at next logon, Create, delete and manage groups, Modify the membership of a group
    and Manage Group Policy links.
  * I choose this scope because admins need to be able to manage user accounts and help trouble shoot like when someone gets locked out due to forgetting their password. Since the groups are Domain local, they won't be able to access all account in the domain, which insures they are acting within their scope. 
