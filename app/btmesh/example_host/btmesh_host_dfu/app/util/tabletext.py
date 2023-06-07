# Copyright 2022 Silicon Laboratories Inc. www.silabs.com
#
# SPDX-License-Identifier: Zlib
#
# The licensor of this software is Silicon Laboratories Inc.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

import textwrap
from collections import namedtuple
from typing import Mapping


def is_namedtuple(obj):
    return (
        isinstance(obj, tuple) and hasattr(obj, "_asdict") and hasattr(obj, "_fields")
    )


HLineFormat = namedtuple("HLineFormat", ["left", "line", "inner", "right"])
RowFormat = namedtuple("RowFormat", ["left", "inner", "right"])
TableTextFormat = namedtuple(
    "TableTextFormat",
    [
        "top_line",
        "header_line",
        "row_line",
        "bottom_line",
        "header_row",
        "data_row",
        "padding",
    ],
)

_tabletext_formats = {
    "simple": TableTextFormat(
        top_line=HLineFormat("", "-", "  ", ""),
        header_line=HLineFormat("", "-", "  ", ""),
        row_line=None,
        bottom_line=HLineFormat("", "-", "  ", ""),
        header_row=RowFormat("", "  ", ""),
        data_row=RowFormat("", "  ", ""),
        padding=1,
    ),
    "grid": TableTextFormat(
        top_line=HLineFormat("+", "-", "+", "+"),
        header_line=HLineFormat("+", "=", "+", "+"),
        row_line=HLineFormat("+", "-", "+", "+"),
        bottom_line=HLineFormat("+", "-", "+", "+"),
        header_row=RowFormat("|", "|", "|"),
        data_row=RowFormat("|", "|", "|"),
        padding=1,
    ),
    "none": TableTextFormat(
        top_line=None,
        header_line=None,
        row_line=None,
        bottom_line=None,
        header_row=RowFormat(None, None, None),
        data_row=RowFormat(None, None, None),
        padding=1,
    ),
}


def _render_line(columns_width, line_fmt: HLineFormat):
    line_elems = []
    if line_fmt.left:
        line_elems.append(line_fmt.left)
    for idx, col_w in enumerate(columns_width, 1):
        if line_fmt.line:
            line_elems.append(line_fmt.line * col_w)
        if idx < len(columns_width) and line_fmt.inner:
            line_elems.append(line_fmt.inner)
    if line_fmt.right:
        line_elems.append(line_fmt.right)
    return "".join(line_elems)


def _render_row(row, columns, columns_width, pad, row_fmt: RowFormat):
    columns_lines = []
    row_lines = []
    row_filtered_values = [row.get(col, "") for col in columns]
    for idx, text in enumerate(row_filtered_values, 0):
        columns_lines.append(_cell_text_to_lines(text, columns_width[idx], pad))
    text_done = [False] * len(columns_lines)
    while not all(text_done):
        row_text_lines = []
        for idx in range(len(columns_lines)):
            if 0 < len(columns_lines[idx]):
                row_text_lines.append(columns_lines[idx].pop(0))
            else:
                row_text_lines.append("")
                text_done[idx] = True
        if any(text for text in row_text_lines):
            line = _render_row_line(row_text_lines, columns_width, row_fmt)
            row_lines.append(line)
    return row_lines


def _render_row_line(row_text_lines, columns_width, row_fmt: RowFormat):
    line_elems = []
    if row_fmt.left:
        line_elems.append(row_fmt.left)
    for idx, text in enumerate(row_text_lines, 0):
        format_str = "{:^" + str(columns_width[idx]) + "}"
        line_elems.append(format_str.format(text))
        if (idx + 1) < len(columns_width) and row_fmt.inner:
            line_elems.append(row_fmt.inner)
    if row_fmt.right:
        line_elems.append(row_fmt.right)
    return "".join(line_elems)


def _cell_text_to_lines(text, col_w, pad):
    lines = []
    words = text.split()
    col_w_char = col_w - 2 * pad
    return textwrap.wrap(text, width=col_w_char)


def _render_table_text(
    rows, columns, columns_width, headers_on, table_fmt: TableTextFormat
):
    table_lines = []
    if table_fmt.top_line:
        line = _render_line(columns_width, table_fmt.top_line)
        table_lines.append(line)
    if headers_on:
        if table_fmt.header_row:
            lines = _render_row(
                columns, columns, columns_width, table_fmt.padding, table_fmt.data_row
            )
            table_lines.extend(lines)
        if table_fmt.header_line:
            line = _render_line(columns_width, table_fmt.top_line)
            table_lines.append(line)
    for row_ctnr, row in enumerate(rows, 1):
        lines = _render_row(
            row, columns, columns_width, table_fmt.padding, table_fmt.data_row
        )
        table_lines.extend(lines)
        if table_fmt.row_line and row_ctnr < len(rows):
            line = _render_line(columns_width, table_fmt.row_line)
            table_lines.append(line)
    if table_fmt.bottom_line:
        line = _render_line(columns_width, table_fmt.top_line)
        table_lines.append(line)
    return table_lines


def _calc_border_width(column_count, table_fmt):
    border_w = 0
    if table_fmt.data_row:
        if table_fmt.data_row.left:
            border_w += 1
        if table_fmt.data_row.right:
            border_w += 1
        if table_fmt.data_row.inner:
            border_w += column_count - 1
    return border_w


def _rows_to_dict_list(rows, columns_provided):
    rows_of_dicts = []
    for row in rows:
        if is_namedtuple(row):
            row_data = row._asdict()
        elif isinstance(row, Mapping):
            row_data = row
        else:
            if not columns_provided:
                raise ValueError(
                    "Table rows are not dicts or namedtuples but columns is not specified."
                )
            row_data = vars(row)
        # Dictionary conversion
        rows_of_dicts.append({k: str(v) for k, v in row_data.items()})
    return rows_of_dicts


def _calc_column_stats(rows, min_col_data_w):
    max_col_data_w = {}
    avg_col_data_w = {}
    for row in rows:
        for field, value in row.items():
            value_len = len(value)
            if field not in max_col_data_w:
                max_col_data_w[field] = max(value_len, min_col_data_w)
            else:
                max_col_data_w[field] = max(max_col_data_w[field], value_len)
            if field not in avg_col_data_w:
                avg_col_data_w[field] = value_len
            else:
                avg_col_data_w[field] += value_len
    for field in avg_col_data_w:
        avg_col_data_w[field] = round(avg_col_data_w[field] / len(rows))
    return max_col_data_w, avg_col_data_w


def table_text(
    rows,
    headers_on=True,
    width=None,
    width_max=None,
    column_min_width=5,
    columns_rel_width=None,
    columns_abs_width=None,
    columns={},
    table_fmt="grid",
):
    table_lines = table_text_lines(
        rows,
        headers_on=headers_on,
        width=width,
        width_max=width_max,
        column_min_width=column_min_width,
        columns_rel_width=columns_rel_width,
        columns_abs_width=columns_abs_width,
        columns=columns,
        table_fmt=table_fmt,
    )
    return "\n".join(table_lines)


def table_text_lines(
    rows,
    headers_on=True,
    width=None,
    width_max=None,
    column_min_width=5,
    columns_rel_width=None,
    columns_abs_width=None,
    columns={},
    table_fmt="grid",
):
    # Dictionaries are ordered from Python 3.7 and the required python
    # version is 3.7 as well so the dict can be considered ordered
    table_fmt = _tabletext_formats[table_fmt]
    pad = table_fmt.padding
    columns_provided = bool(columns)

    if not (rows or columns_provided):
        raise ValueError(
            "Table can't be constructed because neither rows "
            "nor columns were provided."
        )

    # Avoid the modification of mutable default parameter
    if not columns_provided:
        columns = {}
    elif not isinstance(columns, Mapping):
        columns = {column: column for column in columns}

    if columns_abs_width:
        columns_width = columns_abs_width
        col_w_rel = False
    elif columns_rel_width:
        columns_width = columns_rel_width
        col_w_rel = True
    else:
        columns_width = []
        col_w_rel = True

    if columns_rel_width and columns_abs_width:
        raise ValueError(
            "Table columns_rel_width and columns_abs_width are mutually exclusive."
        )
    if width and width_max:
        raise ValueError("Table width and width_max are mutually exclusive.")
    if columns and columns_width and len(columns) != len(columns_width):
        raise ValueError("Table columns and columns_width len is inconsistent.")
    if width and columns_width and (not col_w_rel):
        raise ValueError("Table width and fix columns_width are mutually exclusive.")
    if (not width) and (columns_width and col_w_rel):
        raise ValueError(
            "Table width is mandatory when relative columns_width is used."
        )

    # This function supports rows with different types so in order to handle
    # those the same way in the code all objects are converted into dictionaries
    rows = _rows_to_dict_list(rows, columns_provided)

    if not columns_provided:
        for row in rows:
            for field, value in row.items():
                if field not in columns:
                    columns[field] = field
    if columns_width and len(columns) != len(columns_width):
        raise ValueError("Table columns_width and columns length shall be the same.")

    border_w = _calc_border_width(len(columns), table_fmt)

    max_col_data_w, avg_col_data_w = _calc_column_stats(
        [columns] + rows if headers_on else rows, column_min_width
    )

    total_width_from_col_max = sum([max_col_data_w[col] for col in columns])
    # Two padding spaces around the column content
    total_width_from_col_max += 2 * pad * len(columns)
    # Border characters if present
    total_width_from_col_max += border_w

    final_width = 0
    if columns_width and (not col_w_rel):
        final_width = sum(columns_width) + border_w
    elif width:
        final_width = width
    else:
        final_width = total_width_from_col_max
    min_width = column_min_width * len(columns) + border_w
    if final_width < min_width:
        raise ValueError("Table width is less than the minimum.")

    final_columns_width = []
    if columns_width and (not col_w_rel):
        final_columns_width = columns_width
    elif (
        ((not width) and (not width_max))
        or (width_max and (final_width <= width_max))
        or (width and total_width_from_col_max <= width)
    ):
        for col in columns:
            final_columns_width.append(max_col_data_w[col] + pad)
    else:
        if width_max and width_max < final_width:
            final_width = width_max
        if columns_width and col_w_rel:
            total_cm_width = sum(columns_width)
            final_columns_width = [
                round(final_width * cw / total_cm_width) for cw in columns_width
            ]
        else:
            avg_col_data_w_ordered = [avg_col_data_w[col] + pad for col in columns]
            total_cm_width = sum(avg_col_data_w_ordered)
            final_columns_width = [
                round((final_width - border_w) * col_w_data / total_cm_width)
                for col_w_data in avg_col_data_w_ordered
            ]
    final_columns_width = [
        max(col_w, column_min_width) for col_w in final_columns_width
    ]
    # Adjust the size of columns based on the table width
    width_diff = sum(final_columns_width) + border_w - final_width

    modifications = 0xFFFFFFFF
    while width_diff != 0 and modifications:
        modifications = 0
        if len(columns) < abs(width_diff):
            delta = abs(width_diff) // len(columns)
        else:
            delta = 1
        for idx in range(len(columns)):
            if width_diff < 0:
                modifications += 1
                final_columns_width[idx] += delta
                width_diff += delta
            elif 0 < width_diff:
                if min_width < final_columns_width[idx]:
                    modifications += 1
                    final_columns_width[idx] -= delta
                    width_diff -= delta
    for col_w in final_columns_width:
        if col_w < column_min_width:
            raise ValueError("Table column length is less than the minimum.")
    return _render_table_text(rows, columns, final_columns_width, headers_on, table_fmt)
