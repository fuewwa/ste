# Security Policy

## Reporting a Vulnerability

**Please do not report security issues through public issues, pull requests, or discussions.**

Use one of the following private channels:

1. GitHub private vulnerability reporting: open the **Security** tab of this repository and choose **Report a vulnerability**.
2. Email: `kurwa.offc@proton.me`

Please include as much of the following as you can:

- A short description of the issue and the affected component or file.
- The version or commit where you found it.
- Step-by-step instructions to reproduce it, or a minimal proof of concept.
- The impact: what an attacker can achieve and under which conditions.
- Any suggested fix or mitigation, if you have one.

## What to Expect

| Stage                        | Target time                      |
| ---------------------------- | -------------------------------- |
| Acknowledgement of report    | Within 7 days                    |
| Initial assessment           | Within 14 days                   |
| Fix or mitigation released   | Within 30 days, depending on severity |

We will keep you informed about progress and let you know when the issue is resolved. If you have not received an acknowledgement within 7 days, please send a follow-up.

## Disclosure Policy

We follow coordinated disclosure. Please keep the details private until a fix is available or 90 days have passed since your report, whichever comes first. Once the issue is fixed, we will publish an advisory and, if you wish, credit you for the discovery.

## Scope

In scope:

- Memory safety issues such as buffer overflows, use-after-free, and out-of-bounds access.
- Arbitrary code execution, privilege escalation, and sandbox escapes.
- Injection flaws, path traversal, and unsafe handling of untrusted input.
- Leaks of secrets, credentials, or sensitive data.
- Vulnerabilities in bundled or vendored dependencies that are exploitable through this project.

Out of scope:

- Bugs with no security impact.
- Issues that require physical access or an already fully compromised system.
- Vulnerabilities in third-party software that are not exploitable through this project.
- Reports produced solely by automated scanners without a demonstrated impact.
- Denial of service through unrealistic resource exhaustion.

## Guidelines for Reporting

- Explain **why** the behavior is a security issue, not only that a bug exists.
- Keep reports concise and focused.
- Report issues one at a time so each can be handled properly.
- Do not access, modify, or destroy data that does not belong to you while testing.

## AI-Assisted Reports

AI tools are welcome as an aid, but every report must be reviewed and verified by a human before submission. Reports that are unverified, speculative, or clearly generated without understanding the code will be closed without action. Repeated low-quality submissions may result in a ban from the repository.

## Safe Harbor

If you make a good-faith effort to follow this policy, we will not pursue legal action against you and will work with you to understand and resolve the issue.
