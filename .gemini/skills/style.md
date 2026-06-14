<skill>
  <description>
    When the user invokes `/style`, perform a comprehensive review of all `.cpp` and `.hpp` files in the workspace.
  </description>

  <instructions>
    <step>Find all `.cpp` and `.hpp` files in the workspace (excluding external libraries like `_deps`).</step>
    <step>Evaluate their formatting and style strictly against the Google C++ Style Guide.</step>
    <step>Point out any deviations (e.g., naming conventions, bracket placements, missing headers, or spacing issues), presenting them in a markdown table format with columns for File, Issue Description, and Corrected Snippet. Ensure that the corrected snippets inside the table are formatted within proper markdown code blocks (using backticks) so they are easy to read.</step>
    <step>Provide an overall summary of the codebase's style quality.</step>
    <step>Save the final report in markdown format in the `review/style/` directory, using the current date and time in the file name (e.g., `review/style/style_report_YYYY-MM-DD_HH-MM-SS.md`). Create the directory if it does not exist.</step>
  </instructions>

  <critical_rules>
    <rule>EXCEPTION TO GOOGLE STYLE: You MUST ensure that exactly 4 spaces are used for indentation instead of Google's default 2 spaces. If a file uses 2 spaces, flag it as a formatting error.</rule>
  </critical_rules>
</skill>
