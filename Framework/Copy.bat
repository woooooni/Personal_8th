

//// xcopy /옵션 .복사할파일이 있는 경로			.복사받을경로



xcopy /y/s .\Engine\Public\*.*				.\Reference\Headers\
xcopy /y .\Engine\Bin\*.lib					.\Reference\Librarys\
xcopy /y .\ThirdParty\*.lib					.\Reference\Librarys\





xcopy /y .\Engine\Bin\*.dll					.\Client\Bin\
xcopy /y .\Engine\Bin\*.dll					.\Server\Bin\
xcopy /y .\Engine\Bin\ShaderFiles\*.*		.\Client\Bin\ShaderFiles\


.\Protocol\GenPackets.bat

