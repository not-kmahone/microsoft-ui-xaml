﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "common.h"
#include "FormSection.h"
#include "RuntimeProfiler.h"
#include "ResourceAccessor.h"
#include "Vector.h"
#include "VectorIterator.h"

FormSection::FormSection()
{
    __RP_Marker_ClassById(RuntimeProfiler::ProfId_Forms);
}

winrt::Size FormSection::MeasureOverride(winrt::Size const& availableSize)
{
    // ### temporary -- these would be properties
    const winrt::Thickness itemPadding = winrt::Thickness{ 0, 4, 0, 4 };

    auto children = Children();
    float height = 0.0;
    float rowWidth = Columns() >= 2 ? 350.0f : 500.0f; // ### magic
    float maxHeight = 0.0;

    for (unsigned i = 0u; i < children.Size(); ++i)
    {
        int column = i % Columns();

        auto child = children.GetAt(i);
        child.Measure({rowWidth, availableSize.Height});

        if (child.DesiredSize().Height > maxHeight)
        {
            maxHeight = child.DesiredSize().Height;
        }

        if (column == Columns() - 1 || i == children.Size() - 1)
        {
            height += maxHeight + (float)itemPadding.Top + (float)itemPadding.Bottom;
            maxHeight = 0.0;
        }
    }

    // ### for now
    return winrt::Size(rowWidth * (float)Columns(), height);
}

winrt::Size FormSection::ArrangeOverride(winrt::Size const& finalSize)
{
    //### probably need this sort of thing eventually
    //if (m_isLayoutInProgress)
    //{
    //    throw winrt::hresult_error(E_FAIL, L"Reentrancy detected during layout.");
    //}

    // ### temporary -- these would be properties
    const winrt::Thickness itemPadding = winrt::Thickness{ 0, 4, 0, 4 };

    auto children = Children();
    float y = 0.0;
    float maxHeight = 0.0;
    float rowWidth = Columns() >= 2 ? 350.0f : 500.0f; // ### magic

    for (unsigned i = 0u; i < children.Size(); ++i)
    {
        auto child = children.GetAt(i);
        float width = child.DesiredSize().Width;
        float height = child.DesiredSize().Height;

        int column = i % Columns();

        child.Arrange(winrt::Rect(column * rowWidth + (float)itemPadding.Left + column * 24, y + (float)itemPadding.Top, rowWidth, height));

        if (height > maxHeight)
        {
            maxHeight = height;
        }

        if (column == Columns() - 1 || i == children.Size() - 1)
        {
            y += maxHeight + (float)itemPadding.Top + (float)itemPadding.Bottom;
            maxHeight = 0.0;
        }
    }

    // ### for now
    return finalSize;
}

void FormSection::OnPropertyChanged(const winrt::DependencyPropertyChangedEventArgs& args)
{
    winrt::IDependencyProperty property = args.Property();
    
    // TODO: Implement
}
