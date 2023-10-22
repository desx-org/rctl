
jui is a data interchage format and programming language that allowes for the storage and transfer of data wich includes a mechanism for descibing the data programatically. In effect, JUI is a single compact and portable executable that includes:

 - Language interepter
 - Package manager
 - Version Control
 - Command Line IDE/Edor 
 - Documentation Generator 
 - Unit Test framework 
 - Debugger

JUI Does not:
 - Include any IO functionality. a JUI object defines data and data transforms. 
 - Prioritize Perfomance. 
 - 

 KEY Targets:
 - The operations a JUI object perfoms are deterministic and absolutley repeatable.
 - JUI package resolution is always deterministic and repeatable. objects import other JUI objects based on Hash functions. 
 - All the information about a jui file is in a single file.  

 -Codespaces:

 backend
 ### devconainer.json 

 - Similar to [Developing inside a Container](https://code.visualstudio.com/docs/devcontainers/containers)
 - Settings Documented in [Introduction to dev containers
 ](https://docs.github.com/github/developing-online-with-codespaces/configuring-codespaces-for-your-project)

  you can specify a repo containing dotfiles (.bashrc, .gitignroe, .editorconfig) See[Personalizing Codespaces](https://docs.github.com/en/codespaces/customizing-your-codespace/personalizing-github-codespaces-for-your-account)


  A codespace can be accessed via [Browser](https://docs.github.com/github/developing-online-with-codespaces/creating-a-codespace) or [Extension](https://docs.github.com/github/developing-online-with-codespaces/using-codespaces-in-visual-studio-code)

  To edit/fork/commit a repo (but not run the code) Using the web IDE. Press `.` edit url replacing `gitub.com` with `github.dev`  

  Codespaces web has keybing (and other) issues that can be resolved by installing as [Progressive Web App](https://learn.microsoft.com/en-us/microsoft-edge/progressive-web-apps-chromium/)(PWA)

 - Use `F1` instead of `Ctrl+Shit+P` in firefox
 - Step over is `Alt+F10`` (instead of `F10`)
 - Step into in the web is `Alt+F11` (instead of `F11`) on Windows browsers.
 
 
 
 
 
### [Introduction to dev containers](https://docs.github.com/en/codespaces/setting-up-your-project-for-codespaces/adding-a-dev-container-configuration/introduction-to-dev-containers) 

Custom or [Default Dev Container](https://docs.github.com/en/codespaces/setting-up-your-project-for-codespaces/adding-a-dev-container-configuration/introduction-to-dev-containers#using-the-default-dev-container-configuration)

Dev Container config files in `.devcontainer` Directory
 - VsCode can add config files for you
 - You can Choose froem pre-defined config files
 - [Using pre-defined Configs](https://docs.github.com/en/codespaces/setting-up-your-project-for-codespaces/adding-a-dev-container-configuration/introduction-to-dev-containers#using-a-predefined-dev-container-configuration)

 - [Creating a custom dev container configuration](https://docs.github.com/en/codespaces/setting-up-your-project-for-codespaces/adding-a-dev-container-configuration/introduction-to-dev-containers#creating-a-custom-dev-container-configuration)
  - Single dev container
  - Different Config for different branches
  - Multiple configs (users choose, perhaps 1 fore each lang)
  - [Applying configuration changes to a codespace](https://docs.github.com/en/codespaces/setting-up-your-project-for-codespaces/adding-a-dev-container-configuration/introduction-to-dev-containers#applying-configuration-changes-to-a-codespace)
 - [Starting from template](https://docs.github.com/en/codespaces/developing-in-codespaces/creating-a-codespace-from-a-template#publishing-to-a-remote-repository)

 ## devcontainer.json
 - `.devcontainer.json`
 - `.devcontainer/devcontainer.json`
 - `.devcontainer/CONFIG1/devcontainer.json`
 - `.devcontainer/CONFIG2/devcontainer.json`

 Don't put things in devcontainer config that are personal settings. Used dotfiles and settings sync [See personalization instructions](https://docs.github.com/en/codespaces/customizing-your-codespace/personalizing-github-codespaces-for-your-account) for that
## [Dev Container SPEC](https://containers.dev/implementors/spec/)

## Dockerfile

- Used to create a codespace every time someone creates a codespace
- Specifide by `{"build": {"dockerfile":FILE}}` Typically located as `devcontainer/Dockerfile`
- `image` property in devcontainer.json is an alternative
- [Default image](https://github.com/devcontainers/images/tree/main/src/universal) is used if no image/dockerfile specified
- [Pre defined containers](https://github.com/devcontainers/images/tree/main/src)   
 
### Settings
 - Workspace Setting in `.vscode/settings.json`
 - Devcontainer Settings in `.devcontaienr.json`: `settings` key
 - Changes to settings are applied on devcontainer creation/rebuild. 
  - changes made outside `/workspace` dir are lost 
  - [Directory Structur Deep Dive](https://docs.github.com/en/codespaces/getting-started/deep-dive#about-the-directory-structure-of-a-codespace)

  ### [Prebuilding codespaces](https://docs.github.com/en/codespaces/prebuilding-your-codespaces)

Prebuilds in Repository-level settings:
  - available:
    - personal accounts
    - organizations on GitHub Team or GitHub Enterprise plans
      - Must add payment method w/ spending limit [Choosing who pays](https://docs.github.com/en/codespaces/managing-codespaces-for-your-organization/choosing-who-owns-and-pays-for-codespaces-in-your-organization)
      - default, when changes pused to repo, GitHub Actions used to update prebuilds.

