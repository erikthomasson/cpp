$file = "AVLTree.h.txt"
$executable = "AVLTree.exe"
$allowedSTDLibraries = "memory","cstdlib","exception","stdexcept","utility","iterator", "vector", "string"

$fileWithoutTxt = $file.Remove($file.Length - 4)

function CheckForFile()
{
    Write-Host "Controlling that file $file exists."

    if(![System.IO.File]::Exists("$PWD\Student_Folder\$file"))
    {
        Write-Host "Error: File '$file' does not exist in the Student_Folder. Exiting..."
        Pause
        Exit
    }
    Write-Host "File exists. Continuing..."
}

function ControllIncludes()
{
    Write-Host "Checking submission for non-allowed standard libraries."
    $files = Get-ChildItem -Path ".\Student_Folder\" -Filter "*.txt"
    ForEach($submissionFile in $files)
    {

        $includes = (Select-String $submissionFile -Pattern '#include\s*<').Line

        $Regex = [Regex]::new("(?<=<)(.*)(?=>)")

        [bool]$allIncludesOk = $true
        ForEach($include in $includes)
        {   
            if(!($Regex.Match($include).Value -in $allowedSTDLibraries))
            {
                Write-Host "`tLibrary:" $Regex.Match($include).Value "in file" $submissionFile "is not allowed to solve this problem."
                $allIncludesOk = $false
            }
        }

        if(!$allIncludesOk)
        {
            Write-Host "Include(s) used in the solutions are not allowed for this assignment."
            Pause
            Exit
        }
    }
}

function Clean()
{
    Write-Host "Cleaning up." 
    (mingw32-make -s clean) 2> $null
    $files = Get-ChildItem -Path ".\Includes" -Filter "*.h"
    ForEach($include in $files)
    {
        Remove-Item (".\Includes\" + $include.Name)
    }
    cd ..
}

function CompileSubmission()
{
    Write-Host "Compiling submission."

    $files = Get-ChildItem -Path ".\Student_Folder\" -Filter "*.txt"
    ForEach($submissionFile in $files)
    {
        $submissionFile = $submissionFile.Name
        $submissionFileWithoutTxt = $submissionFile.Remove($submissionFile.Length - 4)
        Copy-Item "Student_Folder\$submissionFile" -Destination "Compiler_Code\Includes\$submissionFileWithoutTxt"
    }
    cd .\Compiler_Code

    Invoke-Expression "mingw32-make.exe -s" -ErrorVariable errors 2> $null

    if($errors -ne $null)
    {
        Write-Host "Compiler errors written to the file 'Errors.txt'"
        $errors > "..\Errors.txt"
        Write-Host "A submission is not allowed to contain any errors. Exiting..."
        Clean
        Pause
        Exit
    }
    Write-Host "Compiling successfull."
}

function RunUnitTests()
{
    Write-Host "Running Unit Tests." "Output is suppressed"
    Invoke-Expression (".\Bin\$executable") -ErrorVariable errors 2>&1> $null
    

    if($LASTEXITCODE)
    {
        Write-Host "Execution of Unit Tests indicate failure."
        if($errors -ne $null)
        {
            Write-Host "One or more errors created. Writing to file 'ExecutionErrors.txt'"
            $errors > "..\ExecutionErrors.txt"
        }
        Write-Host "All Unit tests must pass for your submission to be assessed. Exiting..."
        Clean
        Pause
        Exit
    }
}

Write-Host $pwd

Write-Host "Starting SubmissionScript for assignment 2"

CheckForFile

ControllIncludes

CompileSubmission

RunUnitTests

Clean

Write-Host "Submission script successfully finished."

Pause